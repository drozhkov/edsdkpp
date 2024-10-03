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

#ifndef __EDSDKPP__H
#define __EDSDKPP__H


#include <unordered_map>

#include "core.hpp"
#include "exception.hpp"
#include "camera-list.hpp"


namespace edsdkpp {

	/// @brief 
	class Edsdkpp {
		size_t m_count;
		std::atomic_flag m_countSync;
		Edsdkpp * m_root;

		Ref m_sdkRef;

	public:
		Edsdkpp()
			: m_count( 0 )
			, m_root( this )
			, m_sdkRef(
				  [this] {
					  SpinlockGuard l( m_root->m_countSync );
					  l.lock();

					  if ( 0 == m_root->m_count ) {
						  EDSDKPP_EXECUTE_EDS_FUNCTION( EdsInitializeSDK );
					  }

					  ++m_root->m_count;
				  },
				  [this] {
					  SpinlockGuard l( m_root->m_countSync );
					  l.lock();

					  --m_root->m_count;

					  if ( 0 == m_root->m_count ) {
						  EdsTerminateSDK();
					  }
				  } )
		{
			m_sdkRef.inc();
		}

		edsdkpp::CameraList CameraList()
		{
			EdsCameraListRef ref;
			EDSDKPP_EXECUTE_EDS_FUNCTION( EdsGetCameraList, &ref );
			return edsdkpp::CameraList( ref );
		}
	};

} // namespace edsdkpp


#endif
