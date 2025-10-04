
#include "gtest/gtest.h"
#include "BigNumberTest.h"
#include "BNExecutor.h"
#include "BigNumber.h"

namespace BigNumTest
{

	void BigNumberTest::SetUp()
	{

	}
	void BigNumberTest::TearDown()
	{
	}

	template <BigNum::MOperator OPERATOR>
	void testOperator(const std::string& sbn1, const std::string& sbn2, const std::string& rst)
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

		EXPECT_EQ(rst, bnRst.getNumber());
	}


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
	void verifyTest(const std::string &oper, const BigNum::MathBigNumber& bn1, const BigNum::MathBigNumber& bn2, 
		const std::string& rst, BigNum::MathBigNumber bnRstOper)
	{
		const std::string& msg(bn1.getNumber() + " " + oper + " " + bn2.getNumber() + " = ");

		std::string strAddReal(msg + rst);
		std::string strAddResult(msg + bnRstOper.getNumber());


		if (!rst.empty()) {
			if (rst != bnRstOper.getNumber()) {
				std::cerr << oper << ":  " << bn1.getNumber() << " with " << bn2.getNumber() << " ERROR : "
					<< " result: " << bnRstOper.getNumber() << " but correct is " << rst << std::endl;
//				return;
			}
		}
		std::cerr << oper << ":  " << bn1.getNumber() << " with " << bn2.getNumber() << " result: "
					<< bnRstOper.getNumber() << std::endl;
		EXPECT_EQ(strAddReal, strAddResult);

	}
	void testAdd(const std::string& sbn1, const std::string& sbn2, const std::string& rst)
	{
		BigNum::MathBigNumber bn1(sbn1);
		BigNum::MathBigNumber bn2(sbn2);

		BigNum::MathBigNumber bnRstAdd = bn1 + bn2;

		verifyTest("+", bn1, bn2, rst, bnRstAdd);
	}

	void testSubtract(const std::string& sbn1, const std::string& sbn2, const std::string& rst)
	{
		BigNum::MathBigNumber bn1(sbn1);
		BigNum::MathBigNumber bn2(sbn2);

		BigNum::MathBigNumber bnRstSub = bn1 - bn2;

		verifyTest("-", bn1, bn2, rst, bnRstSub);
	}


	void testMultiply(const std::string& sbn1, const std::string& sbn2, const std::string& rst)
	{
		BigNum::MathBigNumber bn1(sbn1);
		BigNum::MathBigNumber bn2(sbn2);

		BigNum::MathBigNumber bnRstMul = bn1 * bn2;

		verifyTest("*", bn1, bn2, rst, bnRstMul);
	}



	void testDivide(const std::string& sbn1, const std::string& sbn2, const std::string& rst)
	{
		BigNum::MathBigNumber bn1(sbn1);
		BigNum::MathBigNumber bn2(sbn2);

		BigNum::MathBigNumber bnRstDiv = bn1 / bn2;


		verifyTest("/", bn1, bn2, rst, bnRstDiv);
	}

	void testModule(const std::string& sbn1, const std::string& sbn2, const std::string& rst)
	{
		BigNum::MathBigNumber bn1(sbn1);
		BigNum::MathBigNumber bn2(sbn2);

		BigNum::MathBigNumber bnRstDiv = bn1 % bn2;

		verifyTest("%", bn1, bn2, rst, bnRstDiv);
	}

	TEST(BigNumberTest, testModule)
	{
		testModule("1.33", "1.2", "0.13");
		testModule("6", "3", "0");
		testModule("7", "3", "1");
	}


	TEST(BigNumberTest, testAdd)
	{
		testAdd("-50", "10", "-40");
		testAdd("50", "-10", "40");
		testAdd("-10", "50", "40");
		testAdd("10", "-50", "-40");
		testAdd("10", "2", "12");
		testAdd("10", "-2", "8");
		testAdd("-10", "2", "-8");
		testAdd("-10", "-2", "-12");
		testAdd("2", "10", "12");
		testAdd("-2", "10", "8");
		testAdd("2", "-10", "-8");
		testAdd("-2", "-10", "-12");
		testAdd("1.91", "1.1", "3.01");
		testAdd("1.11", "1.1", "2.21");
		testAdd("1.11", "1.1", "2.21");
		testAdd("-101", "-11", "-112");
		testAdd("101", "11", "112");
		testAdd("101", "-11", "90");
		testAdd("101", "90", "191");
	}

	TEST(BigNumberTest, testSubtract)
	{
		testSubtract("0.25", "0.24", "0.01");
		testSubtract("10.4125", "-2.51", "12.9225");
		testSubtract("10.4125", "2.51", "7.9025");
		testSubtract("12.3", "1.5", "10.8");
		testSubtract("10.91", "2.1", "8.81");
		testSubtract("-10.91", "2.1", "-13.01");
		testSubtract("14.325", "12.324", "2.001");
		testSubtract("2", "10", "-8");
		testSubtract("2", "-10", "12");
		testSubtract("-2", "10", "-12");
		testSubtract("-2", "-10", "8");
		testSubtract("2", "10", "-8");
		testSubtract("2", "-10", "12");
		testSubtract("-2", "10", "-12");
		testSubtract("-2", "-10", "8");
		testSubtract("10", "2", "8");
		testSubtract("10", "-2", "12");
		testSubtract("-10", "2", "-12");
		testSubtract("-10", "-2", "-8");
		testSubtract("2", "10", "-8");
		testSubtract("2", "-10", "12");
		testSubtract("-2", "10", "-12");
		testSubtract("-2", "-10", "8");
		testSubtract("10", "2", "8");
		testSubtract("10", "-2", "12");
		testSubtract("-10", "2", "-12");
		testSubtract("-10", "-2", "-8");
		testSubtract("10", "2", "8");
		testSubtract("10", "-2", "12");
		testSubtract("-10", "2", "-12");
		testSubtract("-10", "-2", "-8");
		testSubtract("4.1", "2", "2.1");
		testSubtract("101", "11", "90");
		testSubtract("10", "11", "-1");
		testSubtract("1000000", "100", "999900");
		testSubtract("1100", "111", "989");
		testSubtract("100", "11", "89");
		testSubtract("10", "11", "-1");
		testSubtract("11", "101", "-90");
		testSubtract("101", "90", "11");
		testSubtract("90", "89", "1");
		testSubtract("90", "90", "0");
		testSubtract("111100", "1111", "109989");
		testSubtract("11443333311111111100", "1144422222221111", "11442188888888889989");
		testSubtract("122387876566565674", "31435454654554", "122356441111911120");
	}

	TEST(BigNumberTest, testMultiply)
	{
		testMultiply("123456", "12345", "1524064320");
		testMultiply("5.00", "5.0025", "25.0125");
		testMultiply("6.25", "6.25", "39.0625");
		testMultiply("0.25", "0.25", "0.0625");
		testMultiply("0.025", "0.025", "0.000625");
		testMultiply("0.5", "0.5", "0.25");
		testMultiply("5", "6", "30");
		testMultiply("5", "-6", "-30");
		testMultiply("-5", "6", "-30");
		testMultiply("-5", "-6", "30");
		testMultiply("12", "34", "408");
		testMultiply("45", "10", "450");
		testMultiply("458", "6508", "2980664");
		testMultiply("458", "608", "278464");
		testMultiply("4508", "658", "2966264");
		testMultiply("458", "658", "301364");
		testMultiply("12", "12", "144");
		testMultiply("12", "-12", "-144");
		testMultiply("-12", "-12", "144");
		testMultiply("1234567890", "2", "2469135780");
		testMultiply("2", "1234567890", "2469135780");
		testMultiply("12345678901234567890", "2", "24691357802469135780");
		testMultiply("2", "12345678901234567890", "24691357802469135780");
		testMultiply("123456", "12345", "1524064320");

	}

	TEST(BigNumberTest, testDivide)
	{
		testDivide("7", "3", "2.33333");
		testDivide("101", "2", "50.5");
		testDivide("802", "2", "401");
		testDivide("5780246", "2", "2890123");
		testDivide("24691357802469135780", "2", "12345678901234567890");
		testDivide("0.0254", "35.69", "0.00071");
		testDivide("20", "2", "10");
		testDivide("24691357802469135780", "12345678901234567890", "2");
		testDivide("6.15", "5", "1.23");
		testDivide("6", "88", "0.06818");
		testDivide("1.003", "0.02", "50.15");
		testDivide("181", "4", "45.25");
		testDivide("60", "88", "0.68181");
		testDivide("600", "88", "6.81818");
		testDivide("6", "88", "0.06818");
		testDivide("71", "88", "0.80681");
		testDivide("25.1", "29.19", "0.85988");
		testDivide("1.7", "2.19", "0.77625");
		testDivide("1", "2", "0.5");
		testDivide("10", "2.5", "4");
		testDivide("11.595", "5", "2.319");
		testDivide("13.986882", "5.1234", "2.73");
		testDivide("2.78", "1.59", "1.74842");
		testDivide("12", "2.5", "4.8");
		testDivide("12345.6", "256", "48.225");
		testDivide("10", "3", "3.33333");
		testDivide("181", "4", "45.25");
		testDivide("123456", "55", "2244.65454");
		testDivide("12.2907", "5.3", "2.319");
		testDivide("61.5", "5", "12.3");
		testDivide("12345.6", "256", "48.225");
		testDivide("123456", "256", "482.25");
		testDivide("10", "2", "5");
		testDivide("29835", "65", "459");
		testDivide("473097", "881", "537");


	}

	TEST(BigNumberTest, testOperation)
	{
		testOperation("1.91+1.1", "3.01");
		testOperation("4.1 - 2", "2.1");
		testOperation("2.1 + 2.11 - 4", "0.21");
		testOperator<BigNum::MOperator::Add>("101", "11", "112");
		testOperator<BigNum::MOperator::Subtract>("10", "11", "-1");
		testOperation("-10 +50", "40");
		testOperation("180 +(-10)", "170");
		testOperation("181 / 4", "45.25");
		testOperation("101 -11", "90");
		testOperation("10 -11", "-1");
		testOperation("(55+88)*(66/33)", "286");
		testOperation("(55+88)+(66/33) + (8*8)", "209");
		testOperation("(3 *(5+8))+(6/3) * (8/2)", "47");
	}


	TEST(BigNumberTest, testRotate)
	{
		auto leftrotate = [](std::string& s, size_t d)
		{
			std::rotate(s.begin(), s.begin() + d, s.end());
		};

		// In-place rotates s towards right by d
		auto rightrotate = [&](std::string& s, size_t d)
		{
			leftrotate(s, s.length() - d);
		};

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

		EXPECT_EQ("12345678900", s);
	}

	
}


