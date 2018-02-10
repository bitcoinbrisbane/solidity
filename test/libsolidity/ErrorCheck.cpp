/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file ErrorCheck.cpp
 * @author Yoichi Hirai <i@yoichihirai.com>
 * @date 2016
 */

#include <test/libsolidity/ErrorCheck.h>
#include <libdevcore/Exceptions.h>

#include <string>

using namespace std;

bool dev::solidity::searchErrorMessage(Error const& _err, std::string const& _substr)
{
	if (string const* errorMessage = _err.comment())
	{
		if (errorMessage->find(_substr) == std::string::npos)
		{
			cout << "Expected message \"" << _substr << "\" but found \"" << *errorMessage << "\".\n";
			return false;
		}
		return true;
	}
	else
		cout << "Expected error message but found none." << endl;
	return _substr.empty();
}

bool dev::solidity::searchErrors(ErrorList const& _errors, Error::Type _type, string const& _substr)
{
	for (auto const& error: _errors)
		if (error->type() == _type && error->comment() && error->comment()->find(_substr) != string::npos)
			return true;
	cout << "Expected error message \"" << _substr << "\" not found or wrong type of errror." << endl;
	for (auto const& error: _errors)
		if (error->comment())
			cout << "Message: " << *error->comment() << endl;
	return false;
}
