---
Language:        Cpp
# BasedOnStyle:  LLVM
AccessModifierOffset: -4
ConstructorInitializerIndentWidth: 4
AlignEscapedNewlinesLeft: false
AlignTrailingComments: true
AllowAllParametersOfDeclarationOnNextLine: true
AllowShortIfStatementsOnASingleLine: false
AllowShortLoopsOnASingleLine: false
AllowShortFunctionsOnASingleLine: false
AlwaysBreakTemplateDeclarations: true
AlwaysBreakBeforeMultilineStrings: false
BreakBeforeBinaryOperators: false
BreakBeforeTernaryOperators: true
BreakConstructorInitializersBeforeComma: false
BinPackParameters: true
ColumnLimit:    96 
ConstructorInitializerAllOnOneLineOrOnePerLine: false
DerivePointerBinding: false
ExperimentalAutoDetectBinPacking: false
IndentCaseLabels: false
MaxEmptyLinesToKeep: 1
NamespaceIndentation: None
ObjCSpaceAfterProperty: false
ObjCSpaceBeforeProtocolList: true
PenaltyBreakBeforeFirstCallParameter: 19
PenaltyBreakComment: 300
PenaltyBreakString: 1000
PenaltyBreakFirstLessLess: 120
PenaltyExcessCharacter: 1000000
PenaltyReturnTypeOnItsOwnLine: 60
PointerBindsToType: true
SpacesBeforeTrailingComments: 1
Cpp11BracedListStyle: false
Standard:        Cpp03
IndentWidth:     4
TabWidth:        8
UseTab:          Never
BreakBeforeBraces: Allman
IndentFunctionDeclarationAfterType: false
SpacesInParentheses: false
SpacesInAngles:  false
SpaceInEmptyParentheses: false
SpacesInCStyleCastParentheses: false
SpacesInContainerLiterals: true
SpaceBeforeAssignmentOperators: true
ContinuationIndentWidth: 4
CommentPragmas:  '^ IWYU pragma:'
SpaceBeforeParens: ControlStatements
...
#-8<-
#include <vector>

class Example
{
    class Member
    {
    public:
        struct Comparer
        {
            virtual ~Comparer() {}
            virtual int compareRecordRecord(
                void const* lhsRec, void const* rhsRec) const noexcept = 0;
            virtual int compareRecordValue(void const* lhsRec, void const* rhsVal) const noexcept = 0;
            virtual int compareValueRecord(void const* lhsVal, void const* rhsRec) const noexcept = 0;
            virtual int compareValueValue(void const* lhsVal, void const* rhsVal) const noexcept = 0;
            virtual Comparer *clone() const noexcept = 0;
        };
    };
};
