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

#ifndef __EDSDKPP__CAMERA__H
#define __EDSDKPP__CAMERA__H


#include <string_view>

#include "core.hpp"
#include "properties.hpp"


namespace edsdkpp {

	enum class Switch { On, Off };


	class Camera : public HasProperties {
	public:
		using t_objectEventHandler = std::function<void( EdsObjectEvent inEvent, const HasRef & inRef )>;
		using t_propertyEventHandler =
			std::function<void( EdsPropertyEvent inEvent, EdsPropertyID inPropertyID, EdsUInt32 inParam )>;

	private:
		PropertiesEnableMap m_propertiesEnableMap;

		t_objectEventHandler m_objectEventHandler;
		t_propertyEventHandler m_propertyEventHandler;

	protected:
		static EdsError EDSCALLBACK edsppObjectEventHandler(
			EdsObjectEvent inEvent, EdsBaseRef inRef, EdsVoid * inContext )
		{

			auto _this = static_cast<Camera *>( inContext );
			_this->OnObjectEvent( inEvent, inRef );
			return EDS_ERR_OK;
		}

		static EdsError EDSCALLBACK edsppPropertyEventHandler(
			EdsPropertyEvent inEvent, EdsPropertyID inPropertyID, EdsUInt32 inParam, EdsVoid * inContext )
		{

			auto _this = static_cast<Camera *>( inContext );
			_this->OnPropertyEvent( inEvent, inPropertyID, inParam );
			return EDS_ERR_OK;
		}

		void OnObjectEvent( EdsObjectEvent inEvent, EdsBaseRef inRef )
		{
			EDSDKPP_CALL_FUNC( m_objectEventHandler, inEvent, inRef );
		}

		void OnPropertyEvent( EdsPropertyEvent inEvent, EdsPropertyID inPropertyID, EdsUInt32 inParam )
		{
			EDSDKPP_CALL_FUNC( m_propertyEventHandler, inEvent, inPropertyID, inParam );
		}

	public:
		Camera( EdsBaseRef ref )
			: HasProperties( ref )
		{
		}

		void ObjectEventHandler( const t_objectEventHandler & handler )
		{
			m_objectEventHandler = handler;
			EDSDKPP_EXECUTE_EDS_FUNCTION(
				EdsSetObjectEventHandler, m_baseRef, kEdsObjectEvent_All, edsppObjectEventHandler, this );
		}

		void PropertyEventHandler( const t_propertyEventHandler & handler )
		{
			m_propertyEventHandler = handler;
			EDSDKPP_EXECUTE_EDS_FUNCTION(
				EdsSetPropertyEventHandler, m_baseRef, kEdsPropertyEvent_All, edsppPropertyEventHandler, this );
		}

		auto ProductName()
		{
			return getStringProperty( kEdsPropID_ProductName );
		}

		auto EvfMode()
		{
			return getU32Property( kEdsPropID_Evf_Mode );
		}

		void EvfMode( EdsUInt32 v )
		{
			setProperty( kEdsPropID_Evf_Mode, v );
		}

		EdsUInt32 EvfOutputDevice()
		{
			return getU32Property( kEdsPropID_Evf_OutputDevice );
		}

		void EvfOutputDevice( EdsUInt32 v )
		{
			setProperty( kEdsPropID_Evf_OutputDevice, v );
		}

		void SaveTo( EdsUInt32 v )
		{
			setProperty( kEdsPropID_SaveTo, v );
		}

		EdsUInt32 FixedMovie()
		{
			return getU32Property( kEdsPropID_FixedMovie );
		}

		void MovieParam( EdsUInt32 v )
		{
			setProperty( kEdsPropID_MovieParam, v );
		}

		void MovieSelectSw( Switch s )
		{
			if ( Switch::On == s ) {
				EDSDKPP_EXECUTE_EDS_FUNCTION( EdsSendCommand, m_baseRef, kEdsCameraCommand_MovieSelectSwON, 0 );
			}
			else if ( Switch::Off == s ) {
				EDSDKPP_EXECUTE_EDS_FUNCTION( EdsSendCommand, m_baseRef, kEdsCameraCommand_MovieSelectSwOFF, 0 );
			}
		}

		void enableProperty( EdsUInt32 id )
		{
			setProperty( 0x01000000, id, m_propertiesEnableMap.EnableParam( id ) );
		}

		void openSession()
		{
			EDSDKPP_EXECUTE_EDS_FUNCTION( EdsOpenSession, m_baseRef );
		}

		void closeSession()
		{
			EdsCloseSession( m_baseRef );
		}
	};

} // namespace edsdkpp


#endif
