#pragma once

#ifndef _BNEXECUTOR_H
#define _BNEXECUTOR_H

//**************************************************************************************
//*
//*		Info:
//*
//*		Date: AAAA/MM/DD
//*		Author: Rogerio Regis
//*
//*************************************************************************************


#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include <stack>


#include "BNOperatorMath.h"
#include "BNNotationMath.h"


namespace BigNum
{
	//**************************************************************************************
	//*
	//*		Interface INewClass
	//*
	//*************************************************************************************

	class IBNExecutor
	{
	public:
		using Pointer = std::unique_ptr<IBNExecutor>;
		virtual ~IBNExecutor() = default;


	};
}
namespace BigNum
{

	//**************************************************************************************
	//*	
	//*		class IceServer
	//*
	//*************************************************************************************
	class BNExecutor
		: public IBNExecutor
	{
	public:
		using Pointer = std::shared_ptr<BNExecutor>;
		using StackWork = std::stack<MathBigNumber>;

		template<typename ...Args>
		Pointer static create(Args &&...arg)
		{
			struct EnaleMakeShared
				: public BNExecutor
			{
				EnaleMakeShared(Args &&...arg)
					: BNExecutor(std::forward<Args>(arg)...)
				{}
			};
			Pointer result(std::make_unique<EnaleMakeShared>(std::forward<Args>(arg)...));
			return(std::move(result));
		}
		virtual ~BNExecutor() = default;

		explicit BNExecutor(const MathBigNumber& bnTerm1) {}


		//BNExecutor(const BNExecutor&) = delete;
		//BNExecutor(BNExecutor&&) = delete;
		//const BNExecutor& operator=(const BNExecutor&) = delete;

		template <MOperator OPERATOR>
		MathBigNumber execute(const MathBigNumber& bnTerm1, const MathBigNumber& bnTerm2, bool bForce = false)
		{
			return(MathBigNumber());
		}

		template <>
		MathBigNumber execute<MOperator::Add>
			(const MathBigNumber& bnTerm1, const MathBigNumber& bnTerm2, bool bForce)
		{

			MathBigNumber bnResult;

			if ((bForce) ||
				(bnTerm1.getSignal() == bnTerm2.getSignal())) {
				return(doEexecute<MOperator::Add>(bnTerm1, bnTerm2));
			} 

			MathBigNumber bnSub1(bnTerm1);
			MathBigNumber bnSub2(bnTerm2);
			bnResult = execute<MOperator::Subtract>(bnSub1, bnSub2, true);
	
			return(bnResult);
		}


		template <>
		MathBigNumber execute<MOperator::Subtract>
			(const MathBigNumber& bnTerm1, const MathBigNumber& bnTerm2, bool bForce) 
		{
			MathBigNumber bnResult;

			if ((bForce) ||
				(bnTerm1.getSignal() == bnTerm2.getSignal())) {
				bnResult = doEexecute<MOperator::Subtract>(bnTerm1, bnTerm2);
				return(bnResult);
			}

			MathBigNumber bnAdd1(bnTerm1);
			MathBigNumber bnAdd2(bnTerm2);
			bnResult = execute<MOperator::Add>(bnAdd1, bnAdd2, true);
			bnResult.setSignal(bnTerm1.getSignal());

			return(bnResult);
		}

		template <>
		MathBigNumber execute<MOperator::Multiply>
			(const MathBigNumber& bnTerm1, const MathBigNumber& bnTerm2, bool bForce)
		{

			MathBigNumber bnResult = doEexecute<MOperator::Multiply>(bnTerm1, bnTerm2);

			if (bnTerm1.getSignal() != bnTerm2.getSignal()) {
				bnResult.setSignal(Signal::Negative);
			}
			return(bnResult);
		}


		template <>
		MathBigNumber execute<MOperator::Divide>
			(const MathBigNumber& bnTerm1, const MathBigNumber& bnTerm2, bool bForce)
		{

			MathBigNumber bnResult = doEexecute<MOperator::Divide>(bnTerm1, bnTerm2);

			if (bnTerm1.getSignal() != bnTerm2.getSignal()) {
				bnResult.setSignal(Signal::Negative);
			}
			return(bnResult);
		}

		template <>
		MathBigNumber execute<MOperator::Module>
			(const MathBigNumber& bnTerm1, const MathBigNumber& bnTerm2, bool bForce)
		{

			MathBigNumber bnResult = doEexecute<MOperator::Module>(bnTerm1, bnTerm2);

			if (bnTerm1.getSignal() != bnTerm2.getSignal()) {
				bnResult.setSignal(Signal::Negative);
			}
			return(bnResult);
		}



		MathBigNumber execute(const std::string& infix)
		{
			try {
				return(executeExpression(infix));
			}
			catch (const std::exception&) {

			}

			// return error without exception
			MathBigNumber BigNumber("-0");
			return(BigNumber);
			
		}
		MathBigNumber executeExpression(const std::string& infix)
		{
			BigNum::BNNotationMath::Pointer bnNotationMath =
				BigNum::BNNotationMath::create(infix);

			bnNotationMath->convertToPostfix();

			BNNotationMath::PostFixStack& postFixStack =
				bnNotationMath->getPostFixStack();

			StackWork sWworkStack;


			while (!postFixStack.empty()) {
				BNNotationMath::PairPostFix pairPostFix = postFixStack.top();
				switch (pairPostFix.first) {
					case NotationType::digit:
						sWworkStack.push(MathBigNumber(pairPostFix.second));
						break;
					default: {
						MathBigNumber bnTermY;
						MathBigNumber bnTermX;
						if (sWworkStack.size() > 1) {
							bnTermY = MathBigNumber(sWworkStack.top());
							sWworkStack.pop();
							bnTermX = MathBigNumber(sWworkStack.top());
							sWworkStack.pop();
						}
						else {
							bnTermX = MathBigNumber("0");
							bnTermY = MathBigNumber(sWworkStack.top());
							sWworkStack.pop();
						}
						switch (pairPostFix.first) {
							case NotationType::add:
								sWworkStack.push(execute<MOperator::Add>(bnTermX, bnTermY));
								break;
							case NotationType::subtract:
								sWworkStack.push(execute<MOperator::Subtract>(bnTermX, bnTermY));
								break;
							case NotationType::multiply:
								sWworkStack.push(execute<MOperator::Multiply>(bnTermX, bnTermY));
								break;
							case NotationType::divide:
								sWworkStack.push(execute<MOperator::Divide>(bnTermX, bnTermY));
								break;
							case NotationType::module:
								sWworkStack.push(execute<MOperator::Module>(bnTermX, bnTermY));
								break;

						}
					}

				}
			postFixStack.pop();

			}
			
			if (sWworkStack.size() == 0) {
				return(MathBigNumber("0"));
			}
			return(sWworkStack.top());
		}


		MathBigNumber operator/=(const MathBigNumber& bnTerm)
		{
			return(bnTerm);
		}
	private:

		explicit BNExecutor()
		{

		}

		template <MOperator OPERATOR>
		MathBigNumber doEexecute(const MathBigNumber& bnTerm1, const MathBigNumber& bnTerm2)
		{
			typename BNOperatorMath<OPERATOR>::Pointer bnOper = 
				BNOperatorMath<OPERATOR>::create();

			return(bnOper->execute(bnTerm1, bnTerm2));
		}



	private:

	
	};

	BigNum::MathBigNumber operator+(const BigNum::MathBigNumber& bnTerm1, const BigNum::MathBigNumber& bnTerm4)
	{
		BigNum::BNExecutor::Pointer bnExecutor = BigNum::BNExecutor::create();
		return(bnExecutor->execute<MOperator::Add>(bnTerm1, bnTerm4));
	}
	BigNum::MathBigNumber operator-(const BigNum::MathBigNumber& bnTerm1, const BigNum::MathBigNumber& bnTerm4)
	{
		BigNum::BNExecutor::Pointer bnExecutor = BigNum::BNExecutor::create();
		return(bnExecutor->execute<MOperator::Subtract>(bnTerm1, bnTerm4));
	}
	BigNum::MathBigNumber operator*(const BigNum::MathBigNumber& bnTerm1, const BigNum::MathBigNumber& bnTerm4)
	{
		BigNum::BNExecutor::Pointer bnExecutor = BigNum::BNExecutor::create();
		return(bnExecutor->execute<MOperator::Multiply>(bnTerm1, bnTerm4));
	}
	BigNum::MathBigNumber operator/(const BigNum::MathBigNumber& bnTerm1, const BigNum::MathBigNumber& bnTerm4)
	{
		BigNum::BNExecutor::Pointer bnExecutor = BigNum::BNExecutor::create();
		return(bnExecutor->execute<MOperator::Divide>(bnTerm1, bnTerm4));
	}
	BigNum::MathBigNumber operator%(const BigNum::MathBigNumber& bnTerm1, const BigNum::MathBigNumber& bnTerm4)
	{
		BigNum::BNExecutor::Pointer bnExecutor = BigNum::BNExecutor::create();
		return(bnExecutor->execute<MOperator::Module>(bnTerm1, bnTerm4));
	}
}


#endif // !_NEWCLASS_H_

