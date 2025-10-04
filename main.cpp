#include <string>
#include <iostream>
#include <stack>
#include <vector>


#include "BNExecutor.h"
#include "BNOperatorRelat.h"
#include "BNNotationMath.h"






int testNotation(const std::string& infix)
{

	BigNum::BNNotationMath::Pointer bnNotationMath =
		BigNum::BNNotationMath::create(infix);

	
	bnNotationMath->convertToPostfix();

	
	
	return 0;
}


template <BigNum::MOperator OPERATOR>
void testOperator(const std::string& sbn1, const std::string& sbn2, const std::string& rst = "")
{
	BigNum::MathBigNumber bn1(sbn1);
	BigNum::MathBigNumber bn2(sbn2);

	typename BigNum::BNOperatorMath<OPERATOR>::Pointer bnOper =
		BigNum::BNOperatorMath<OPERATOR>::create();

	BigNum::MathBigNumber bnRst = bnOper->execute(bn1, bn2);

	if (!rst.empty()) {
		if (rst != bnRst.getNumber()) {
			std::cout << bnOper->getOperatorType() << ": " << bn1.getNumber() << " <== " << bn2.getNumber() << " ERROR: "
				<< " result: " << bnRst.getNumber() << " but correct is " << rst << std::endl;
			return;
		}
		
	}

	std::cout << bnOper->getOperatorType() << ": " << bn1.getNumber() << " <== " << bn2.getNumber()  
		<< " result: " << bnRst.getNumber() << std::endl;
}

//void testCompare(const std::string& sbn1, const std::string& sbn2, BigNum::ROperator rOPerator)
//{
//	BigNum::MathBigNumber bn1(sbn1);
//	BigNum::MathBigNumber bn2(sbn2);
//
//	BigNum::BNOperatorRelat::Pointer bnOperCmp = BigNum::BNOperatorRelat::create();
//
//	BigNum::ROperator rOPeratorRst = bnOperCmp->execute(bn1, bn2);
//
//	if (rOPeratorRst != rOPerator) {
//		std::cout << "Cmp:  " << bn2.getNumber() << " of " << bn1.getNumber() << " ERROR: "
//			<< " result: " << (int)rOPeratorRst << " but correct is " << (int)rOPerator << std::endl;
//
//		return;
//	}
//	
//	std::cout << "Cmp:  " << bn2.getNumber() << " of " << bn1.getNumber() << " result: " << (int)rOPeratorRst << std::endl;
//
//}
//
void testOperation(const std::string& infix, const std::string& rst = "")
{
	
	BigNum::BNExecutor::Pointer bnExecutor = BigNum::BNExecutor::create();

	BigNum::MathBigNumber bnRstOper = bnExecutor->execute(infix);

	if (!rst.empty()) {
		if (rst != bnRstOper.getNumber()) {
			std::cout << "Operation :  " << infix << " ERROR: "
				<< " result: " << bnRstOper.getNumber() << " but correct is " << rst << std::endl;
			return;
		}
	}
	std::cout << "Operation:  " << infix << " result: " << bnRstOper.getNumber() << std::endl;

}

void testAdd(const std::string& sbn1, const std::string& sbn2, const std::string& rst = "")
{
	BigNum::MathBigNumber bn1(sbn1);
	BigNum::MathBigNumber bn2(sbn2);

	BigNum::MathBigNumber bnRstAdd = bn1 + bn2;

	if (!rst.empty()) {
		if (rst != bnRstAdd.getNumber()) {
			std::cout << "Add:  " << bn2.getNumber() << " plus " << bn1.getNumber() << " ERROR: "
				<< " result: " << bnRstAdd.getNumber() << " but correct is " << rst << std::endl;
			return;
		}
	}
	std::cout << "Add:  " << bn1.getNumber() << " plus " << bn2.getNumber() << " result: " << bnRstAdd.getNumber() << std::endl;
}

void testSubtract(const std::string& sbn1, const std::string& sbn2, const std::string &rst="")
{
	BigNum::MathBigNumber bn1(sbn1);
	BigNum::MathBigNumber bn2(sbn2);

	BigNum::MathBigNumber bnRstSub = bn1 - bn2;

	if (!rst.empty()) {
		if (rst != bnRstSub.getNumber()) {
			std::cout << "Sub:  " << bn2.getNumber() << " of " << bn1.getNumber() << " ERROR: "
				<< " result: " << bnRstSub.getNumber() <<  " but correct is " << rst << std::endl;
			return;
		}
	}
	std::cout << "Sub:  " << bn2.getNumber() << " of " << bn1.getNumber() << " result: " << bnRstSub.getNumber() << std::endl;

}


void testMultiply(const std::string& sbn1, const std::string& sbn2, const std::string& rst = "")
{
	BigNum::MathBigNumber bn1(sbn1);
	BigNum::MathBigNumber bn2(sbn2);

	BigNum::MathBigNumber bnRstMul = bn1 * bn2;

	if (!rst.empty()) {
		if (rst != bnRstMul.getNumber()) {
			std::cout << "Mul:  " << bn1.getNumber() << " by " << bn2.getNumber() << " ERROR: "
				<< " result: " << bnRstMul.getNumber() << " but correct is " << rst << std::endl;
			return;
		}
	}
	std::cout << "Mul:  " << bn1.getNumber() << " by " << bn2.getNumber() << " result: " << bnRstMul.getNumber() << std::endl;

}



void testDivide(const std::string& sbn1, const std::string& sbn2, const std::string& rst = "")
{
	BigNum::MathBigNumber bn1(sbn1);
	BigNum::MathBigNumber bn2(sbn2);

	BigNum::MathBigNumber bnRstDiv = bn1 / bn2;


	if (!rst.empty()) {
		if (rst != bnRstDiv.getNumber()) {
			std::cout << "Div:  " << bn1.getNumber() << " by " << bn2.getNumber() << " ERROR: "
				<< " result: " << bnRstDiv.getNumber() << " but correct is " << rst << std::endl;
			return;
		}
	}
	std::cout << "Div:  " << bn1.getNumber() << " by " << bn2.getNumber() << " result: " << bnRstDiv.getNumber() << std::endl;

}


void leftrotate(std::string& s, size_t d)
{
	std::rotate(s.begin(), s.begin() +d, s.end());
}

// In-place rotates s towards right by d
void rightrotate(std::string& s, size_t d)
{
	leftrotate(s, s.length() - d);
}

int main(int argc, char* argv[])
{
	std::string s("12345678900");
	int d = 1;
	while (true) {
		rightrotate(s, 1);
		size_t stopPos = s.find_first_not_of('0', 0);
		if (stopPos > 0) {
			leftrotate(s, 1);
			break;
		}
		s.erase(0, stopPos);
	}


	
	//
	//testCompare("458", "458", BigNum::ROperator::Equal);
	//testCompare("458", "658", BigNum::ROperator::Less);
	//testCompare("658", "458", BigNum::ROperator::Greater);

	



	return(0);
}