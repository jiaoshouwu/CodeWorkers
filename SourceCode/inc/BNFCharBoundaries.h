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

#ifndef _BNFCharBoundaries_h_
#define _BNFCharBoundaries_h_

#include "GrfBlock.h"

namespace CodeWorker {
	class DtaBNFScript;
	class BNFClause;
	class ExprScriptVariable;


	class BNFCharBoundaries : public GrfCommand {
	private:
		DtaBNFScript* _pBNFScript;
		int _iStartChar;
		int _iEndChar;
		ExprScriptVariable* _pVariableToAssign;
		bool _bConcatVariable;
		std::vector<std::string> _listOfConstants;
		int _iClauseReturnType;
		bool _bContinue;
		bool _bNoCase;

	public:
		BNFCharBoundaries(DtaBNFScript* pBNFScript, GrfBlock* pParent, int iStartChar, int iEndChar, bool bContinue, bool bNoCase);
		virtual ~BNFCharBoundaries();

		virtual void accept(DtaVisitor& visitor, DtaVisitorEnvironment& env);

		virtual bool isABNFCommand() const;

		void setVariableToAssign(ExprScriptVariable* pVariableToAssign, bool bConcat, BNFClause& theClause);
		inline void setConstantsToMatch(const std::vector<std::string>& listOfConstants) { _listOfConstants = listOfConstants; }

		virtual void compileCpp(CppCompilerEnvironment& theCompilerEnvironment) const;
		virtual std::string toString() const;

	protected:
		virtual SEQUENCE_INTERRUPTION_LIST executeInternal(DtaScriptVariable& visibility);
	};
}

#endif
