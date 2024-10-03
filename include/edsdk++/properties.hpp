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

#ifndef __EDSDKPP__PROPERTIES__H
#define __EDSDKPP__PROPERTIES__H


#include <unordered_map>

#include "core.hpp"


#define EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( a_p, a_paramEnable )                                                   \
	{                                                                                                                  \
		static_cast<EdsUInt32>( a_p ), static_cast<EdsUInt32>( a_paramEnable )                                         \
	}


namespace edsdkpp {

	enum class PropertyId : EdsUInt32 {
		kEdsPropID_Evf_ViewType = 0x01000513,
		kEdsPropID_MovieSoundRecord = 0x01000427,
		kEdsPropID_ShutterType = 0x01000461,
		kEdsPropID_RegisterFocusEdge = 0x0100046c,
		kEdsPropID_DriveFocusToEdg = 0x0100046d,
		kEdsPropID_FocusPosition = 0x0100046e
	};


	class PropertiesEnableMap {
		std::unordered_map<EdsUInt32, EdsUInt32> m_map;

	public:
		PropertiesEnableMap()
			: m_map( { EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_UTCTime, 0x51DD2696 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_TimeZone, 0xFA71F7 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_SummerTimeSetting, 0x9780670 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_Evf_ClickWBCoeffs, 0x653048A9 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_ManualWhiteBalanceData, 0x20DD3609 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_MirrorUpSetting, 0x517F095D ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_MirrorLockUpState, 0x00E13499 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_FixedMovie, 0x17AF25B1 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_MovieParam, 0x2A0C1274 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_TempStatus, 0x14840DF1 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_EVF_RollingPitching, 0x5B3740D ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_AutoPowerOffSetting, 0x1C31565B ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_Aspect, 0x3FB1718B ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_Evf_VisibleRect, 0x4D2879F3 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_StillMovieDivideSetting, 0x1EDD16B6 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_CardExtension, 0x4FB44E3C ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_MovieCardExtension, 0x5C6C20B2 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_StillCurrentMedia, 0x139E4D1D ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_MovieCurrentMedia, 0x00D50906 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_FocusShiftSetting, 0x707571DF ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_MovieHFRSetting, 0x44396197 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_AFEyeDetect, 0x7C89405C ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_MovieServoAf, 0x74A63CC9 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( PropertyId ::kEdsPropID_Evf_ViewType, 0x7CBD2BB7 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( PropertyId ::kEdsPropID_MovieSoundRecord, 0x3E032C31 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( PropertyId ::kEdsPropID_ShutterType, 0x4C157D57 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_AFTrackingObject, 0xC78510D ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( kEdsPropID_ContinuousAfMode, 0x32F87FF6 ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( PropertyId ::kEdsPropID_RegisterFocusEdge, 0x5B960B1C ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( PropertyId ::kEdsPropID_DriveFocusToEdg, 0x5AB16AAC ),
				  EDSDKPP_PROPERTY_ENABLE_PARAM_MAP_ITEM( PropertyId ::kEdsPropID_FocusPosition, 0x5F745B48 ) } )
		{
		}

		EdsUInt32 EnableParam( EdsUInt32 propertyId )
		{
			return m_map[propertyId];
		}
	};

} // namespace edsdkpp


#endif
