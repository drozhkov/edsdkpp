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

#ifndef __EDSDKPP__EXCEPTION__H
#define __EDSDKPP__EXCEPTION__H


#include <exception>
#include <string>
#include <string_view>

#include "core.hpp"


namespace edsdkpp {

	class EdsdkppException : public std::exception {
		EdsError m_error;
		std::string m_message;

	public:
		EdsdkppException( const std::string_view message, EdsError e )
			: m_message(message)
			, m_error( e )
		{
		}

		EdsError Error() const
		{
			return m_error;
		}

		const char * what() const noexcept override
		{
			return m_message.c_str();
		}
	};

} // namespace edsdkpp


#endif
