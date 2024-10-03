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

#ifndef __EDSDKPP__CAMERA_LIST__H
#define __EDSDKPP__CAMERA_LIST__H


#include "core.hpp"
#include "camera.hpp"


namespace edsdkpp {

	class CameraList : public HasRef {
	public:
		EdsUInt32 Count()
		{
			EdsUInt32 result;
			EDSDKPP_EXECUTE_EDS_FUNCTION( EdsGetChildCount, m_baseRef, &result );
			return result;
		}

		edsdkpp::Camera Camera( EdsInt32 index )
		{
			EdsBaseRef ref;
			EDSDKPP_EXECUTE_EDS_FUNCTION( EdsGetChildAtIndex, m_baseRef, index, &ref );
			return edsdkpp::Camera( ref );
		}
	};

} // namespace edsdkpp


#endif
