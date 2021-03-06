/*
 * CppParsingTree.h
 *
 * Copyright (C) 1996-1997, 1999-2002 Cedric Lemaire
 *
 */
#ifndef _CppParsingTree_h_
#define _CppParsingTree_h_

/**[description]
[title]CodeWorker in C++[/title]

[chapter]Introduction[/chapter]

A C++ interface is available since version 3.0, for using CodeWorker in C++ applications. This enables calling parse and
generation tasks directly from C++. Hence, the C++ application can handle the parse tree, iterating node arrays,
accessing to subtrees (the attributes) and so on. Moreover, the developer has all native functions of the
CodeWorker scripting language at his disposal.

[chapter]Calling CodeWorker from C++[/chapter]

There are some points to know before using CodeWorker in a C++ software.

[section]C++ library and some compulsory header files[/section]
Once you have downloaded CodeWorker, you'll find the directory "cpp" just below the main directory of the
setup. This directory concerns all about CodeWorker in C++. The C++ static release library is directly available under
the "cpp" directory, in "cpp/JNICodeWorker.dll" (Windows only; for other platforms, "libcodeworker.a" stands in the
root path of CodeWorker). The C++ headers declaring the API with the library, are delivered in "cpp/include".

From here, you have to add the C++ library to your project (Makefile, VC++ solution, ...) and to add an include
path pointing to the C++ headers.

[section]Example[/section]

The following C++ application behaves like a CodeWorker's leader script. It asks for the parsing of a file,
then it generates an HTML file by exploring the parse tree. A very classical process in Design-Specific Modeling.
[code]
#include "CppParsingTree.h"
#include "CGCompiler.h"
#include "CGRuntime.h"

int main(int, char**) {
	// compile a BNF and parse a DSL
	CodeWorker::CppParsingTree_value tree;
	CodeWorker::CGCompiledBNFScript BNF;
	BNF.buildFromFile("My_DSL_Parser.cwp");
	theBNF.parse(tree, "requirements.dsl");

	// generate the documentation in HTML
	CodeWorker::CGCompiledTemplateScript genDoc;
	genDoc.buildFromFile("docHTML.cwp");
	genDoc.generate(tree, "doc.html");

	// to finish, display of the whole parse
	// tree, up to depth = 4
	CodeWorker::CGRuntime::traceObject(tree, 4);

	return 0;
}
[/code]

The class "CodeWorker::CGCompiledBNFScript" allows the precompilation of an extended-BNF script and its execution. The
execution requires a "CodeWorker::CppParsingTree_value" object as the context to populate.

The class "CodeWorker::CGCompiledTemplateScript" precompiles a template-based script and generates an output file,
traversing the parse tree previously populated by the BNF script.

At the end, the parse tree is displayed, up to a depth of 4, using a classical function of the scripting
language: "traceObject()". All functions of the scripting language are accessible via the class "CodeWorker::CGRuntime".

[chapter]The C++ API of CodeWorker[/chapter]

[section]CodeWorker::CppParsingTree_value[/section]

This class represents a CodeWorker variable, able to contain an association table, to have some attributes (branches through subtrees),
to be worth a string value or to point to another parse tree.

Example of declaration:
[code]
CodeWorker::CppParsingTree_value tree;
[/code]

The equivalent declaration in CodeWorker is:
[code]
local tree;
[/code]

[subsection]public ParseTree()[/subsection]

This constructor creates an internal parse tree, which will be deleted once the garbage collector will free this
instance. Note that this parse tree will have no name (the property "getName()" will return null).

[subsection]public ParseTree(ParseTree)[/subsection]

This constructor points to another parse tree, but will never delete the internal parse tree it refers to. It is a
kind of copy-by-reference.

Example:
[code]
CodeWorker::CppParsingTree_value secondTree = new CodeWorker::CppParsingTree_value(firstTree);
[/code]

The equivalent declaration in CodeWorker is:
[code]
localref secondTree = firstTree;
[/code]
[subsection]public String getName()[/subsection]

This property returns the name of the node (null if the node was declared on the stack of the Java application).

[subsection]public String getValue() / void setValue(String)[/subsection]

This property contains the string value attached to the node, which may be null.

Example:
[code]
tree.setValue("pink elephant");
System.out.println(tree.getValue());
[/code]

The equivalent in CodeWorker is:
[code]
tree = "pink elephant";
traceLine(tree);
[/code]
[subsection]public ParseTree getReference()[/subsection]

This property is assigned if the node points to another node.

Example:
[code]
secondTree = firstTree.getReference();
[/code]

The equivalent in CodeWorker is:
[code]
ref secondTree = firstTree;
[/code]

[subsection]public ParseTree[] getArray()[/subsection]

This property returns the association table attached to the node. If there is no table, it returns null.

Example:
[code]
CodeWorker::CppParsingTree_value[] nodeArray = tree.getArray();
if (nodeArray != null) {
	for (int j = 0; j < nodeArray.length; ++j) {
		CodeWorker::CGRuntime::traceObject(nodeArray[j]);
	}
}
[/code]

The equivalent in CodeWorker is:
[code]
foreach j in tree {
	traceObject(j);
}
[/code]

[subsection]public String[] getAttributeNames()[/subsection]

This property returns all attribute names (branches through subtrees) of the node. This function introspects the
node.

Example:
[code]
String[] list = tree.getAttributeNames();
if (list != null) {
	for (int j = 0; j < list.length; ++j) {
		System.out.println(list[j]);
	}
}
[/code]

The equivalent in CodeWorker is:
[code]
local list;
getVariableAttributes(tree, list);
foreach j in list {
	traceLine(j);
}
[/code]

[subsection]public ParseTree getNode(String attr)[/subsection]

This function returns the subtree attached to an attribute of the node. If the attribute doesn't exist,
it returns null.

Example:
[code]
CodeWorker::CppParsingTree_value nextNode = tree.getNode("expression");
if ((nextNode != null) && (nextNode.getValue() != null)) {
	System.out.println(nextNode.getValue());
}
[/code]

The equivalent in CodeWorker is:
[code]
if tree.expression {
	traceLine(tree.expression);
}
[/code]

[subsection]public ParseTree insertNode(String attr)[/subsection]

This function inserts a new attribute to the node and returns the subtree newly created. If the attribute
already exists, it returns the attached subtree.

Example:
[code]
tree.insertNode("expression").setValue("a + b");
[/code]

The equivalent in CodeWorker is:
[code]
insert tree.expression = "a + b";
[/code]

[/description]
**/

/**[description="CGCompiler.h"/]**/
/**[description="CGRuntime::h"]**/

/**[description]
[chapter]Conclusion[/chapter]

The Java package of CodeWorker allows the developer to drive easily DSL parsing and code generation from the
Java platform. The parse tree can be traversed and decorated directly in Java, rather
than only in the scripting language of CodeWorker.
   [/description]
**/

#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>

namespace CodeWorker {
	class DtaScriptVariable;
	class ExprScriptExpression;
	class ExprScriptVariable;
	class CGRuntime;
	class ExternalValueNode;


	class CppParsingTree_expr {
		protected:
			ExprScriptExpression* _pExpression;

		public:
			inline CppParsingTree_expr() : _pExpression(NULL) {}
			CppParsingTree_expr(const std::string& sExpression);
			~CppParsingTree_expr();

			inline ExprScriptExpression& getExpression() const { return *_pExpression; }
	};

	class CppParsingTree_varexpr : public CppParsingTree_expr {
		public:
			CppParsingTree_varexpr(const std::string& sVariableExpression);

			ExprScriptVariable& getVariableExpression() const;
	};


	class CppParsingTree_var {
		protected:
			DtaScriptVariable* _pInternalNode;
			friend class CGRuntime;
			friend class CGCompiledCommonScript;
			friend class CGCompiledTemplateScript;
			friend class CGCompiledBNFScript;
			friend class CGCompiledTranslationScript;

			CppParsingTree_var();

		public:
			CppParsingTree_var(const CppParsingTree_var& tree);
			CppParsingTree_var(DtaScriptVariable* pVariable);
			CppParsingTree_var(DtaScriptVariable& variable);

			// avoid this accessor, please!
			inline DtaScriptVariable* getInternalNode() const { return _pInternalNode; }

			ExternalValueNode* getExternalValueNode() const;
			inline bool isNull() const { return (_pInternalNode == NULL); }
			bool isLocal() const;
			const char* getName() const;
			const char* getValue() const;
			size_t getValueLength() const;
			bool getBooleanValue() const;
			int getIntValue() const;
			double getDoubleValue() const;
			std::string getStringValue() const;
			DtaScriptVariable* getReference() const;

			void clearValue() const;

			void setValue(const char* tcValue) const;
			void setValue(const std::string& sValue) const;
			void setValue(bool bValue) const;
			void setValue(double dValue) const;
			void setValue(int iValue) const;
			void setValue(const CppParsingTree_var& pValue) const;
			void setValue(ExternalValueNode* pExternal) const;
			void setValue(const std::list<std::string>& listOfValues) const;
			void concatenateValue(const std::string& sValue) const;
			void concatenateValue(const CppParsingTree_var& pValue) const;
			void setReference(const CppParsingTree_var& reference) const;
			void setAll(const CppParsingTree_var& tree) const;
			void merge(const CppParsingTree_var& tree) const;
			CppParsingTree_var pushItem() const;
			void pushItem(const std::string& sValue) const;
			void pushItem(const CppParsingTree_var& theValue) const;
			void addElements(const CppParsingTree_var& theValue) const;
			const std::list<DtaScriptVariable*>* getArray() const;
			const std::map<std::string, DtaScriptVariable*>* getSortedArray() const;
			std::auto_ptr<std::vector<DtaScriptVariable*> > getSortedNoCaseArray() const;
			std::auto_ptr<std::vector<DtaScriptVariable*> > getSortedArrayOnValue() const;
			std::auto_ptr<std::vector<DtaScriptVariable*> > getSortedNoCaseArrayOnValue() const;

			std::list<std::string> getAttributeNames() const;

			void clearNode() const;

			CppParsingTree_var getNode(const std::string& sBranch) const;
			CppParsingTree_var getEvaluatedNode(const std::string& sDynamicVariable) const;
			CppParsingTree_var getOrCreateLocalEvaluatedNode(const std::string& sDynamicVariable) const;
			CppParsingTree_var getParentNode() const;
			CppParsingTree_var getRootNode() const;
			CppParsingTree_var getArrayNodeFromKey(const std::string& sKey) const;
			CppParsingTree_var getArrayNodeFromPosition(int iPosition) const;
			CppParsingTree_var getFirstArrayNode() const;
			CppParsingTree_var getLastArrayNode() const;

			CppParsingTree_var insertNode(const std::string& sBranch) const;
			CppParsingTree_var insertEvaluatedNode(const std::string& sDynamicVariable) const;
			CppParsingTree_var insertClassicalEvaluatedNode(const std::string& sDynamicVariable) const;
			CppParsingTree_var insertArrayNodeFromKey(const std::string& sKey) const;
			CppParsingTree_var insertArrayNodeFromKey(int iKey) const;
			CppParsingTree_var insertArrayNodeFromKey(const CppParsingTree_var& pKey) const;
	};

	class CppParsingTree_value : public CppParsingTree_var {
		public:
			CppParsingTree_value();
			CppParsingTree_value(bool bValue);
			CppParsingTree_value(int iValue);
			CppParsingTree_value(double dValue);
			CppParsingTree_value(const char* tcValue);
			CppParsingTree_value(const std::string& sValue);
			CppParsingTree_value(const CppParsingTree_var& tree);
			CppParsingTree_value(const CppParsingTree_value& tree);
			~CppParsingTree_value();
	};

	class CppParsingTree_global : public CppParsingTree_var {
		public:
			void initialize(const std::string& sName);
	};
}

#endif
