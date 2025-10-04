#pragma once

#ifndef _BNOPERATOR_H_
#define _BNOPERATOR_H_	

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
#include <cmath>

#include "BigNumber.h"
//#include "BNOperatorRelat.h"

namespace BigNum
{
	enum class MOperator : int {
		Add = 0,
		Subtract = 1,
		Multiply = 2,
		Divide = 3,
		Module = 4,
	};
};

namespace BigNum
{
	//**************************************************************************************
	//*
	//*		Interface IBNOperatorMath
	//*
	//*************************************************************************************

	class IBNOperatorMath
	{
	public:
		using Pointer = std::unique_ptr<IBNOperatorMath>;
		explicit IBNOperatorMath() = delete;
		virtual ~IBNOperatorMath() = default;

		//MathBigNumber updateIntegerSize(const MathBigNumber& constBigNumber, size_t size)
		//{

		//	MathBigNumber bigNumber(constBigNumber);

		//	if (constBigNumber.getPartition(0).getSize() < size) {
		//		bigNumber.getInteger().updateSize(size);
		//	}
		//
		//	return(bigNumber);
		//}
		void rogerio()
		{}
		const std::string& getOperatorType() const
		{
			return(operatorType_);
		}

		//virtual BigNumber execute(Partition partition, int& carry, const BigNumber& bnFactor1, const BigNumber& bnFactor2) = 0;
		virtual MathBigNumber execute(const MathBigNumber& bnFactor1, const MathBigNumber& bnFactor2) = 0;

	protected:

		explicit IBNOperatorMath(const std::string& operatorType)
			: operatorType_(operatorType)
		{}

	private:
		const std::string operatorType_;
	};
}
namespace BigNum
{


	//**************************************************************************************
	//*	
	//*		class BNOperatorMath
	//*
	//*************************************************************************************
	template <MOperator OPERATOR>
	class BNOperatorMath
		: public IBNOperatorMath
		
	{
	public:
		virtual ~BNOperatorMath() = default;
		BNOperatorMath(const BNOperatorMath&) = delete;
		BNOperatorMath(BNOperatorMath&&) = delete;
		const BNOperatorMath& operator=(const BNOperatorMath&) = delete;



	private:
		
	};


	//**************************************************************************************
	//*	
	//*		class BNOperatorMath<MOperator::Add>
	//*
	//*************************************************************************************
	template <>
	class BNOperatorMath<MOperator::Add>
		: public IBNOperatorMath
	{
	public:
		using Pointer = std::unique_ptr<BNOperatorMath<MOperator::Add>>;

		template<typename ...Args>
		Pointer static create(Args &&...arg)
		{
			struct EnaleMakeShared
				: public BNOperatorMath<MOperator::Add>
			{
				EnaleMakeShared(Args &&...arg)
					: BNOperatorMath(std::forward<Args>(arg)...)
				{}
			};
			Pointer result(std::make_unique<EnaleMakeShared>(std::forward<Args>(arg)...));
			return(std::move(result));
		}
		virtual ~BNOperatorMath() = default;


		BNOperatorMath(const BNOperatorMath&) = delete;
		BNOperatorMath(BNOperatorMath&&) = delete;
		const BNOperatorMath& operator=(const BNOperatorMath&) = delete;

		MathBigNumber execute(const MathBigNumber& bnTerm1In, const MathBigNumber& bnTerm2In)
		{
			int carry = 0;
			BigNumber bnRstDecimal = execute(Partition::Decimal, carry, bnTerm1In.getDecimal(), bnTerm2In.getDecimal());
			BigNumber bnRstInteger = execute(Partition::Integer, carry, bnTerm1In.getInteger(), bnTerm2In.getInteger());

			Signal signal = Signal::Positive;
			if (bnTerm1In.getSignal() == bnTerm1In.getSignal()) {
				signal = bnTerm1In.getSignal();
			}
			MathBigNumber mathBigNumber(bnRstInteger, bnRstDecimal, signal);

			return(mathBigNumber);
		}
		
		virtual BigNumber execute(Partition partition, const BigNumber& bnTerm1, const BigNumber& bnTerm2)
		{
			int carryZero = 0;
			return (execute(partition, carryZero, bnTerm1, bnTerm2));
		}

		BigNumber execute(Partition partition, int &carry, const BigNumber& bnTerm1, const BigNumber& bnTerm2)
		{
			size_t maxSize = std::max<size_t>(bnTerm1.getSize(), bnTerm2.getSize());
	
			Side side = partition == Partition::Integer ? Side::Right : Side::Left;
			
			const_cast<BigNumber&>(bnTerm1).setSize(side, maxSize);
			const_cast<BigNumber&>(bnTerm2).setSize(side, maxSize);

			BigNumber bnResult(maxSize);


			// Add from right to left separate digit to digit and use carry when 10 ou more
			for (int idx = (int)bnTerm1.getSize() - 1; idx >= 0 ; --idx) {
				int sum = bnTerm1[idx] + bnTerm2[idx] + carry;
				carry = sum / 10;
				bnResult.at((size_t)idx) = sum % 10;
			}
			if (partition == Partition::Integer) {
				bnResult.incrementSize(Side::Right, 1);
				bnResult.at(0) = carry;
				bnResult.ltrim();
			}

			return(bnResult);
		}


	private:
		explicit BNOperatorMath()
			: IBNOperatorMath("Add")
			
		{
		}


	private:


	};


	//**************************************************************************************
	//*	
	//*		class BNOperatorMath<MOperator::Subtract>
	//*
	//*************************************************************************************
	template <>
	class BNOperatorMath<MOperator::Subtract>
		: public IBNOperatorMath
	{
	public:
		using Pointer = std::unique_ptr<BNOperatorMath<MOperator::Subtract>>;

		template<typename ...Args>
		Pointer static create(Args &&...arg)
		{
			struct EnaleMakeShared
				: public BNOperatorMath<MOperator::Subtract>
			{
				EnaleMakeShared(Args &&...arg)
					: BNOperatorMath(std::forward<Args>(arg)...)
				{}
			};
			Pointer result(std::make_unique<EnaleMakeShared>(std::forward<Args>(arg)...));
			return(std::move(result));
		}
		virtual ~BNOperatorMath() = default;


		BNOperatorMath(const BNOperatorMath&) = delete;
		BNOperatorMath(BNOperatorMath&&) = delete;
		const BNOperatorMath& operator=(const BNOperatorMath&) = delete;


		MathBigNumber execute(const MathBigNumber& bnTerm1In, const MathBigNumber& bnTerm2In)
		{
			int carry = 0;
			BigNumber bnRstDecimal = execute(Partition::Decimal, carry, bnTerm1In.getDecimal(), bnTerm2In.getDecimal());
			BigNumber bnRstInteger = execute(Partition::Integer, carry, bnTerm1In.getInteger(), bnTerm2In.getInteger());

			Signal signal= bnTerm1In.getSignal();
			if (carry != 0) {
				signal = bnTerm1In.getSignal() == Signal::Positive ? Signal::Negative : Signal::Positive;
			}
			else {
				signal = bnTerm1In.getSignal();
			}

			MathBigNumber mathBigNumber(bnRstInteger, bnRstDecimal, signal);

			return(mathBigNumber);
		}

		virtual BigNumber execute(Partition partition, const BigNumber& bnTerm1, const BigNumber& bnTerm2)
		{
			int carryZero = 0;
			return (execute(partition, carryZero, bnTerm1, bnTerm2));
		}

		BigNumber execute(Partition partition, int& carry, const BigNumber& bnTerm1, const BigNumber& bnTerm2)
		{
			size_t maxSize = std::max<size_t>(bnTerm1.getSize(), bnTerm2.getSize());

			Side side = (partition == Partition::Integer ? Side::Right : Side::Left);
			const_cast<BigNumber&>(bnTerm1).setSize(side, maxSize);
			const_cast<BigNumber&>(bnTerm2).setSize(side, maxSize);

			BigNumber bnResult(maxSize);

			// Subtract from right to left separate digit to digit and get carry when result is less than 0
			for (int idx = (int)bnTerm1.getSize() - 1; idx >= 0; --idx) {
				int sub = 0;
				if (bnTerm1[idx] < bnTerm2[idx] + carry) {
					sub = (bnTerm1[idx] + 10) - bnTerm2[idx] - carry;
					carry = 1;
				}
				else
					if (bnTerm1[idx] >= bnTerm2[idx]) {
						sub = bnTerm1[idx] - bnTerm2[idx] - carry;
						carry = 0;
					}

				bnResult.at((size_t)idx) = sub;
			}

			if (partition == Partition::Integer) {
				// invert terms an recalculate if 1ft term is less than 2nd term
				if (carry > 0) {
					int carry = 0;
					BigNumber bnResult = execute(partition, carry, bnTerm2, bnTerm1);
					return(bnResult);
				}

				if (partition == Partition::Integer) {
					const_cast<BigNumber&>(bnTerm2).ltrim();
					bnResult.ltrim();
				}
			}

			return(bnResult);
		}



	private:
		explicit BNOperatorMath()
			: IBNOperatorMath("Subtract")
		{
		}



	private:


	};

	//**************************************************************************************
	//*	
	//*		class BNOperatorMath<MOperator::Multiply>
	//*
	//*************************************************************************************
	template <>
	class BNOperatorMath<MOperator::Multiply>
		: public IBNOperatorMath
	{
	public:
		using Pointer = std::unique_ptr<BNOperatorMath<MOperator::Multiply>>;

		template<typename ...Args>
		Pointer static create(Args &&...arg)
		{
			struct EnaleMakeShared
				: public BNOperatorMath<MOperator::Multiply>
			{
				EnaleMakeShared(Args &&...arg)
					: BNOperatorMath(std::forward<Args>(arg)...)
				{}
			};
			Pointer result(std::make_unique<EnaleMakeShared>(std::forward<Args>(arg)...));
			return(std::move(result));
		}
		virtual ~BNOperatorMath() = default;


		BNOperatorMath(const BNOperatorMath&) = delete;
		BNOperatorMath(BNOperatorMath&&) = delete;
		const BNOperatorMath& operator=(const BNOperatorMath&) = delete;

		MathBigNumber execute(const MathBigNumber& bnTerm1In, const MathBigNumber& bnTerm2In)
		{
			int carry = 0;

			BigNumber bnFactor1(bnTerm1In.getInteger());
			bnFactor1.concatenate(bnTerm1In.getDecimal());

			BigNumber bnFactor2(bnTerm2In.getInteger());
			bnFactor2.concatenate(bnTerm2In.getDecimal());

			size_t sizeDecimal = bnTerm1In.getDecimal().getSize() + bnTerm2In.getDecimal().getSize();
			BigNumber bnRstInteger = execute(Partition::Integer, carry, bnFactor1, bnFactor2);
			bnRstInteger.setSize(Side::Right, sizeDecimal);

			BigNumber bnInteger (
				bnRstInteger.getNumber().substr(0, bnRstInteger.getNumber().size() - sizeDecimal));
			bnInteger.setSize(Side::Right, 1);

			BigNumber bnDecimal (
				bnRstInteger.getNumber().substr(bnRstInteger.getNumber().size() - sizeDecimal, std::string::npos));
			bnDecimal.rtrim();

			Signal signal = Signal::Negative;
			if (bnTerm1In.getSignal() == bnTerm2In.getSignal()) {
				signal = Signal::Positive;
			}
			MathBigNumber mathBigNumber(bnInteger, bnDecimal, signal);


			return(mathBigNumber);
		}

		virtual BigNumber execute(Partition partition, const BigNumber& bnFactorY, const BigNumber& bnFactorX)
		{
			int carryZero = 0;
			return (execute(partition, carryZero, bnFactorY, bnFactorX));
		}

		BigNumber execute(Partition partition, int& carry, const BigNumber& bnFactorY, const BigNumber& bnFactorX)
		{

			typename BNOperatorMath<MOperator::Add>::Pointer bnOperAdd =
				BNOperatorMath<MOperator::Add>::create();

			size_t resultSize = std::max<size_t>(bnFactorY.getSize(), bnFactorY.getSize());
			BigNumber bnResult(resultSize);
			
			// multiply from right to left each digit of 2nd term to all digits of 1ft term using carry if necessary 
			for (int idx2 = (int)bnFactorX.getSize() - 1; idx2 >= 0; --idx2) {
				int carry = 0;
				BigNumber bnResultIn(resultSize + 1);
				for (int idx1 = (int)bnFactorY.getSize() - 1; idx1 >= 0; --idx1) {
					int mul = (bnFactorY[idx1] * bnFactorX[idx2]) + carry;
					carry = mul / 10;
					bnResultIn.at((size_t)idx1 + 1) = mul % 10;
				}

				if (carry > 0) {
//					bnResultIn.incrementSize(Side::Right, 1);
					bnResultIn.at(0) = carry;
				}

				// do apropriate displacemnet to left and add all partial result
				bnResultIn.shiftLeft(bnFactorX.getSize() - idx2 - 1);
				bnResult = bnOperAdd->execute(Partition::Integer, bnResult, bnResultIn);
				bnResult.setSize(Side::Right, bnResultIn.getSize());
			}

			if (partition == Partition::Integer) {
				bnResult.ltrim();
			}


			return(bnResult);
		}
	private:
		explicit BNOperatorMath()
			: IBNOperatorMath("Multiply")
		{
		}


	private:


	};

	//**************************************************************************************
	//*	
	//*		class BNOperatorMath<MOperator::Divide>
	//*
	//*************************************************************************************
	template <>
	class BNOperatorMath<MOperator::Divide>
		: public IBNOperatorMath
	{
	public:
		using Pointer = std::unique_ptr<BNOperatorMath<MOperator::Divide>>;

		template<typename ...Args>
		Pointer static create(Args &&...arg)
		{
			struct EnaleMakeShared
				: public BNOperatorMath<MOperator::Divide>
			{
				EnaleMakeShared(Args &&...arg)
					: BNOperatorMath(std::forward<Args>(arg)...)
				{}
			};
			Pointer result(std::make_unique<EnaleMakeShared>(std::forward<Args>(arg)...));
			return(std::move(result));
		}
		virtual ~BNOperatorMath() = default;


		BNOperatorMath(const BNOperatorMath&) = delete;
		BNOperatorMath(BNOperatorMath&&) = delete;
		const BNOperatorMath& operator=(const BNOperatorMath&) = delete;


		MathBigNumber execute(const MathBigNumber& bnDividend, const MathBigNumber& bnDivider)
		{
			return(execute(bnDividend, bnDivider, precision_));
		}

		MathBigNumber execute(const MathBigNumber& bnDividend, const MathBigNumber& bnDivide, int precision)
		{
			int carry = 0;

			if (bnDivide.compare(MathBigNumber("0")) == ROperator::Equal) {
				std::stringstream ss;
				ss << "Error: Invalid division by zero" << std::endl;
				throw (std::exception(ss.str().c_str()));
			}
			size_t sizeDecimal = std::max<size_t>(bnDividend.getDecimal().getSize(), bnDivide.getDecimal().getSize());

			BigNumber bnFactor1Decimal(bnDividend.getDecimal());
			if (bnFactor1Decimal.getSize() < sizeDecimal) {
				bnFactor1Decimal.incrementSize(Side::Left, sizeDecimal - bnFactor1Decimal.getSize());
			}

			BigNumber bnFactor2Decimal(bnDivide.getDecimal());
			if (bnFactor2Decimal.getSize() < sizeDecimal) {
				bnFactor2Decimal.incrementSize(Side::Left, sizeDecimal - bnFactor2Decimal.getSize());
			}

			BigNumber bnFactorY(bnDividend.getInteger());
			bnFactorY.concatenate(bnFactor1Decimal);

			BigNumber bnFactorX(bnDivide.getInteger());
			bnFactorX.concatenate(bnFactor2Decimal);

			bnFactorY.ltrim();
			bnFactorX.ltrim();
			BigNumber bnRstExecute = execute(Partition::Integer, carry, bnFactorY, bnFactorX, precision);

			BigNumber bnDecimal(bnRstExecute.getNumber().substr(carry, std::string::npos));
			BigNumber bnInteger(bnRstExecute.getNumber().substr(0, carry));
			bnInteger.setSize(Side::Right, 1);

			Signal signal = Signal::Negative;
			if (bnDividend.getSignal() == bnDivide.getSignal()) {
				signal = Signal::Positive;
			}
			MathBigNumber mathBigNumber(bnInteger, bnDecimal, signal);
			mathBigNumber.truncate(precision);

			return(mathBigNumber);
		}

		virtual BigNumber execute(Partition partition, const BigNumber& bnFactorY, const BigNumber& bnFactorX, int precision)
		{
			int carryZero = 0;
			return (execute(partition, carryZero, bnFactorY, bnFactorX, precision));
		}


		BigNumber execute(Partition partition, int& carryOut, const BigNumber& bnFactorY, const BigNumber& bnFactorX, int precision)
		{
			carryOut = -1;
			BigNumber bnResult(0);

			auto setCarryOut = [&]() {
				if (carryOut == -1) {
					carryOut = (int)bnResult.getSize();
				}
			};
	
			if (precision == -1) {
				return(bnResult);
			}

			const BigNumber bigNumberZero("0");
			int resultPos = 0;
			BigNumber bnNewToDivide(0);
			size_t partialSize = std::min<size_t>(bnFactorX.getSize(), bnFactorY.getSize());
			
			

			// get digits of dividend from left to right and cocatenate with previous step
			// comparing until the value is more then divider and use this result dividing 
			// by succesive subtraction to discovery partial result of division and repeat this steps until 
			// finalized contatenation
			bool verifyNumber = false;
			BigNumber BNPartialDividend(bnFactorY.getPartialNumber(0, partialSize));
			for (size_t idx = partialSize; idx < bnFactorY.getSize() + 1; ++idx) {
				bnNewToDivide.concatenate(BNPartialDividend);
				if (!processPartialNumber(bnNewToDivide, bnResult, bnFactorX)) {
					verifyNumber = false;
					if (bnNewToDivide.compare(bigNumberZero) == ROperator::Equal) {
						bnResult.shiftLeft(1);
						bnResult.at(bnResult.getSize() - 1) = 0;
						verifyNumber = true;
					}
					BNPartialDividend = BigNumber(bnFactorY.getPartialNumber(idx, 1));
					continue;
				}
				performDivide(bnNewToDivide, bnResult, bnFactorX);
				verifyNumber = true;
				BNPartialDividend = BigNumber(bnFactorY.getPartialNumber(idx, 1));
			}


			if (!verifyNumber) {
				while (!processPartialNumber(bnNewToDivide, bnResult, bnFactorX)) {
					if (bnNewToDivide.compare(bigNumberZero) == ROperator::Equal) {
						break;
					}
					bnResult.shiftLeft(1);
					bnResult.at(bnResult.getSize() - 1) = 0;
					setCarryOut();

					bnNewToDivide.concatenate(bigNumberZero);
				}
				
				performDivide(bnNewToDivide, bnResult, bnFactorX);
			}

			if (bnNewToDivide.compare(BigNumber("0")) == ROperator::Greater) {	// compute rest of division
				bnNewToDivide.concatenate(bigNumberZero);
				setCarryOut();
				BigNumber bnRslDividePrec = execute(partition, bnNewToDivide, bnFactorX, precision - 1);
				bnResult.concatenate(const_cast<BigNumber&>(bnRslDividePrec));
			} 
			else {
				setCarryOut();
			}

//			bnResult.ltrim();

			return(bnResult);
		}
	protected:
		explicit BNOperatorMath(int precision = 5, const std::string &operation ="Divide")
			: precision_(precision),
			IBNOperatorMath(operation)
		{
			bnOperAdd_ = BNOperatorMath<MOperator::Add>::create();
			bnOperSub_ = BNOperatorMath<MOperator::Subtract>::create();
			bnOperMul_ = BNOperatorMath<MOperator::Multiply>::create();
		}

	private:

		bool processPartialNumber(BigNumber& bnNewToDivide, BigNumber& bnResult, const BigNumber& bnFactorX)
		{
			BNOperatorMath<MOperator::Subtract>::Pointer bnOperSub =
				BNOperatorMath<MOperator::Subtract>::create();

			int carry = 0;
			const BigNumber bigNumberZero("0");

			if (bnNewToDivide.getSize() < bnFactorX.getSize()) {
				return(false);
			}

			BigNumber bnRstSub = bnOperSub->execute(Partition::Integer, carry, bnNewToDivide, bnFactorX);
			if (carry == 1) {
				return(false);
			}

			return(true);
		}

		void performDivide(BigNumber& bnNewToDivide, BigNumber& bnResult, const BigNumber& bnFactorX)
		{
			const BigNumber cbnMultiply("1");
			BigNumber bnMultiply(1);

			const BigNumber bnSaveDivide(bnNewToDivide);

			int divRst = 0;
			do {
				++divRst;
				bnMultiply = bnOperAdd_->execute(Partition::Integer, bnMultiply, cbnMultiply);
				bnNewToDivide = bnOperMul_->execute(Partition::Integer, bnFactorX, bnMultiply);
			} while (bnNewToDivide.compare(bnSaveDivide) != ROperator::Greater);

			// back one loop of division (used subtract routine)
			bnResult.shiftLeft(1);
			bnResult.at(bnResult.getSize() - 1) = --divRst;;
			bnNewToDivide = bnOperSub_->execute(Partition::Integer, bnNewToDivide, bnFactorX);

			// calculate new partial dividend
			bnNewToDivide = bnOperSub_->execute(Partition::Integer, bnSaveDivide, bnNewToDivide);

		}

	protected:
		int precision_;

	private:
		
		typename BNOperatorMath<MOperator::Add>::Pointer bnOperAdd_;
		typename BNOperatorMath<MOperator::Subtract>::Pointer bnOperSub_;
		typename BNOperatorMath<MOperator::Multiply>::Pointer bnOperMul_;

	};


	//**************************************************************************************
	//*	
	//*		class BNOperatorMath<MOperator::Module>
	//*
	//*************************************************************************************
	template <>
	class BNOperatorMath<MOperator::Module>
		: public BNOperatorMath<MOperator::Divide>
	{
	public:
		using Pointer = std::unique_ptr<BNOperatorMath<MOperator::Module>>;

		template<typename ...Args>
		Pointer static create(Args &&...arg)
		{
			struct EnaleMakeShared
				: public BNOperatorMath<MOperator::Module>
			{
				EnaleMakeShared(Args &&...arg)
					: BNOperatorMath(std::forward<Args>(arg)...)
				{}
			};
			Pointer result(std::make_unique<EnaleMakeShared>(std::forward<Args>(arg)...));
			return(std::move(result));
		}
		virtual ~BNOperatorMath() = default;


		BNOperatorMath(const BNOperatorMath&) = delete;
		BNOperatorMath(BNOperatorMath&&) = delete;
		const BNOperatorMath& operator=(const BNOperatorMath&) = delete;


		MathBigNumber execute(const MathBigNumber& bnDividend, const MathBigNumber& bnDivider)
		{
			return(execute(bnDividend, bnDivider, precision_));
		}

		MathBigNumber execute(const MathBigNumber& bnDividend, const MathBigNumber& bnDivide, int precision)
		{
			MathBigNumber mathBigNumber = 
				BNOperatorMath<MOperator::Divide>::execute(bnDividend, bnDivide, 10);

			MathBigNumber mathBNDecimal(BigNumber("0"), mathBigNumber.getDecimal(), mathBigNumber.getSignal());
			
			MathBigNumber mathBNMul = bnOperMul_->execute(mathBNDecimal, bnDivide);
			const MathBigNumber bnRounder = mathBNMul.getMathBNRound(precision);
			if (bnRounder.getDecimal().getSize() == 0) {
				return(mathBNMul);
			}

			MathBigNumber mathBNAdd = bnOperAdd_->execute(mathBNMul, bnRounder);
			mathBNAdd.truncate(bnDividend.getDecimal().getSize());

			return(mathBNAdd);
		}

		virtual BigNumber execute(Partition partition, const BigNumber& bnFactorY, const BigNumber& bnFactorX, int precision)
		{
			int carryZero = 0;
			return (execute(partition, carryZero, bnFactorY, bnFactorX, precision));
		}


		BigNumber execute(Partition partition, int& carryOut, const BigNumber& bnFactorY, const BigNumber& bnFactorX, int precision)
		{

			return(BNOperatorMath<MOperator::Divide>::execute(partition, carryOut, bnFactorY, bnFactorX, precision));
		}
	private:
		explicit BNOperatorMath(int precision = 5)
			: BNOperatorMath<MOperator::Divide>(precision, "Module")
		{
			bnOperAdd_ = BNOperatorMath<MOperator::Add>::create();
			bnOperMul_ = BNOperatorMath<MOperator::Multiply>::create();
		}



	private:
		typename BNOperatorMath<MOperator::Add>::Pointer bnOperAdd_;
		typename BNOperatorMath<MOperator::Multiply>::Pointer bnOperMul_;

	};


}


#endif // !_BNOperatorMath_H_

