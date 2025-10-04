#pragma once

#ifndef BIGNUMBER_H_TEST
#define BIGNUMBER_H_TEST

#include "BigNumber.h"
#include "BNOperatorMath.h"

namespace BigNumTest
{
	class BigNumberTest
		: public ::testing::Test
	{
	protected:

		virtual void SetUp();
		virtual void TearDown();
	
		template <BigNum::MOperator OPERATOR>
		void testOperator(const std::string& sbn1, const std::string& sbn2, const std::string& rst = "");
		void testOperation(const std::string& infix, const std::string& rst = "");
		void testAdd(const std::string& sbn1, const std::string& sbn2, const std::string& rst = "");
		void testSubtract(const std::string& sbn1, const std::string& sbn2, const std::string& rst = "");
		void testMultiply(const std::string& sbn1, const std::string& sbn2, const std::string& rst = "");
		void testDivide(const std::string& sbn1, const std::string& sbn2, const std::string& rst = "");
		void testModule(const std::string& sbn1, const std::string& sbn2, const std::string& rst);

	};

}
#endif
