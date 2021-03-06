/* "CodeWorker":	a scripting language for parsing and generating text.

Copyright (C) 1996-1997, 1999-2002 C�dric Lemaire

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

To contact the author: codeworker@free.fr
*/

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include "DtaScriptVariable.h"
#include "ExprScriptExpression.h"
#include "ScpStream.h"
#include "CppCompilerEnvironment.h"
#include "GrfWhile.h"


namespace CodeWorker {
	GrfWhile::~GrfWhile() {
		delete _pCondition;
	}

	SEQUENCE_INTERRUPTION_LIST GrfWhile::executeInternal(DtaScriptVariable& visibility) {
		SEQUENCE_INTERRUPTION_LIST result = NO_INTERRUPTION;
		do {
			std::string sCondition = _pCondition->getValue(visibility);
			if (sCondition.empty()) break;
			result = GrfBlock::executeInternal(visibility);
			switch(result) {
				case CONTINUE_INTERRUPTION:
					result = NO_INTERRUPTION;
				case NO_INTERRUPTION: break;
				case BREAK_INTERRUPTION: return NO_INTERRUPTION;
				default:
					return result;

			}
		} while (true);
		return result;
	}

	void GrfWhile::compileCpp(CppCompilerEnvironment& theCompilerEnvironment) const {
		CW_BODY_INDENT << "while (";
		_pCondition->compileCppBoolean(theCompilerEnvironment, false);
		CW_BODY_STREAM << ") ";
		GrfBlock::compileCpp(theCompilerEnvironment);
	}
}
