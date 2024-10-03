/*
 *	Copyright (c) 2024 Denis Rozhkov <denis@rozhkoff.com>
 *	This file is part of edsdk++.
 *
 *	edsdk++ is free software: you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or (at your
 *	option) any later version.
 *
 *	edsdk++ is distributed in the hope that it will be
 *	useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 *	Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License along with
 *	edsdk++. If not, see <https://www.gnu.org/licenses/>.
 */

// SPDX-FileCopyrightText: 2024 Denis Rozhkov <denis@rozhkoff.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef __EDSDKPP__CORE__H
#define __EDSDKPP__CORE__H


#include <utility>
#include <atomic>
#include <functional>
#include <span>

#include "EDSDK.h"

#include "exception.hpp"


#define EDSDKPP_EXECUTE_EDS_FUNCTION( a_name, ... )                                                                    \
	{                                                                                                                  \
		auto l_edsError = a_name( __VA_ARGS__ );                                                                       \
		if ( EDS_ERR_OK != l_edsError ) {                                                                              \
			throw EdsdkppException(                                                                                    \
				std::string( #a_name ) + ": " + std::to_string( static_cast<int>( l_edsError ) ), l_edsError );        \
		}                                                                                                              \
	}

#define EDSDKPP_CALL_FUNC( a_f, ... )                                                                                  \
	{                                                                                                                  \
		auto f = a_f;                                                                                                  \
                                                                                                                       \
		if ( a_f ) {                                                                                                   \
			a_f( __VA_ARGS__ );                                                                                        \
		}                                                                                                              \
	}


namespace edsdkpp {

	class SpinlockGuard {
	protected:
		std::atomic_flag & m_lock;
		size_t m_cycleCount;

	public:
		SpinlockGuard( std::atomic_flag & f )
			: m_lock( f )
		{
		}

		~SpinlockGuard()
		{
			unlock();
		}

		void lock()
		{
			m_cycleCount = 0;

			while ( m_lock.test_and_set() ) {
				m_cycleCount++;
				m_lock.wait( true );
			}
		}

		void unlock()
		{
			m_lock.clear();
			m_lock.notify_one();
		}
	};


	class Ref {
		std::function<void()> m_inc;
		std::function<void()> m_dec;

	public:
		Ref( const std::function<void()> & inc, const std::function<void()> & dec )
			: m_inc( inc )
			, m_dec( dec )
		{
		}

		Ref()
		{
		}

		Ref( const Ref & other )
			: Ref( other.m_inc, other.m_dec )
		{
			inc();
		}

		Ref( Ref && o )
			: m_inc( std::exchange( o.m_inc, [] {} ) )
			, m_dec( std::exchange( o.m_dec, [] {} ) )
		{
		}

		~Ref()
		{
			dec();
		}

		Ref & operator=( const Ref & other )
		{
			dec();
			m_inc = other.m_inc;
			m_dec = other.m_dec;
			inc();
			return *this;
		}

		Ref & operator=( Ref && other )
		{
			dec();
			m_inc = std::exchange( other.m_inc, [] {} );
			m_dec = std::exchange( other.m_dec, [] {} );
			return *this;
		}

		void inc()
		{
			EDSDKPP_CALL_FUNC( m_inc );
		}

		void dec()
		{
			EDSDKPP_CALL_FUNC( m_dec );
		}
	};


	class HasRef {
		Ref m_ref;

	protected:
		EdsBaseRef m_baseRef;

	public:
		HasRef( EdsBaseRef baseRef )
			: m_baseRef( baseRef )
			, m_ref( [this] { EdsRetain( m_baseRef ); }, [this] { EdsRelease( m_baseRef ); } )
		{
		}

		EdsBaseRef V() const
		{
			return m_baseRef;
		}
	};


	class HasProperties : public HasRef {
	protected:
		EdsUInt32 getPropertySize( EdsPropertyID id, EdsInt32 param = 0 )
		{
			EdsDataType dataType;
			EdsUInt32 size;
			EDSDKPP_EXECUTE_EDS_FUNCTION( EdsGetPropertySize, m_baseRef, id, param, &dataType, &size );

			return size;
		}

		void getProperty( EdsPropertyID id, std::span<uint8_t> result, EdsInt32 param = 0 )
		{
			EDSDKPP_EXECUTE_EDS_FUNCTION( EdsGetPropertyData, m_baseRef, id, param, result.size(), result.data() );
		}

		template <typename T> void getProperty( EdsPropertyID id, std::vector<T> & result, EdsInt32 param = 0 )
		{
			if ( result.size() == 0 ) {
				result.resize( getPropertySize( id, param ) / sizeof( T ) );
			}

			getProperty( id,
				std::span<uint8_t>( reinterpret_cast<uint8_t *>( result.data() ), result.size() * sizeof( T ) ),
				param );
		}

		EdsUInt32 getU32Property( EdsPropertyID id, EdsInt32 param = 0 )
		{
			EdsUInt32 result;
			getProperty( id, std::span<uint8_t>( reinterpret_cast<uint8_t *>( &result ), sizeof( EdsUInt32 ) ), param );
			return result;
		}

		std::string getStringProperty( EdsPropertyID id, EdsInt32 param = 0 )
		{
			std::vector<uint8_t> p;
			getProperty( id, p, param );
			return std ::string( p.begin(), p.end() );
		}

		void setProperty( EdsPropertyID id, std::span<uint8_t> v, EdsInt32 param = 0 )
		{
			EDSDKPP_EXECUTE_EDS_FUNCTION( EdsSetPropertyData, m_baseRef, id, param, v.size(), v.data() );
		}

		void setProperty( EdsPropertyID id, EdsUInt32 v, EdsInt32 param = 0 )
		{
			setProperty( id, std::span( reinterpret_cast<uint8_t *>( &v ), sizeof v ), param );
		}

	public:
		HasProperties( EdsBaseRef ref )
			: HasRef( ref )
		{
		}

		std::vector<EdsInt32> PropertyDesc( EdsPropertyID id )
		{
			EdsPropertyDesc d;
			EDSDKPP_EXECUTE_EDS_FUNCTION( EdsGetPropertyDesc, m_baseRef, id, &d );
			return std::vector<EdsInt32>( d.propDesc, d.propDesc + d.numElements );
		}
	};

} // namespace edsdkpp


#endif
