#pragma once


#ifndef _BIGNUMBER_H_
#define _BIGNUMBER_H_

#include <string>
#include <sstream>
#include <algorithm>
#include <exception>


namespace BigNum
{
	enum class ROperator : int {
		Less = -1,
		Equal = 0,
		Greater = 1,
	};

	enum class Partition : int {
		Integer = 0,
		Decimal = 1,
	};

	enum class Side : int {
		Right = 0,
		Left = 1,
	};

	enum class Signal : int {
		Null = 0,
		Positive = 1,
		Negative = 2,
	};
};
namespace BigNum
{
	//**************************************************************************************
	//*	
	//*		class BigNumber
	//*
	//*************************************************************************************

	class BigNumber
	{
	public:
		BigNumber(const BigNumber& bigNumber)
			: sBigNumber_(bigNumber.sBigNumber_)
		{
		}
		BigNumber(size_t size)
		{
			setSize(Side::Right, size);
		}

		explicit BigNumber(const std::string& sBigNumber)
			: sBigNumber_(sBigNumber)
		{
			replaceNumber(sBigNumber);
		}

		const BigNumber& operator=(const BigNumber& bigNumber)
		{
			this->sBigNumber_ = bigNumber.sBigNumber_;
			this->at_ = 0;
			return(*this);
		}
		int operator[](int idx) const
		{
			char digit = sBigNumber_[idx];

			return(static_cast<int>(digit) - 48);
		}

		inline virtual const std::string& getNumber() const
		{
			return(sBigNumber_);
		}

		inline const std::string getPartialNumber(size_t start, size_t stop) const
		{
			return(sBigNumber_.substr(start, stop));
		}
		inline size_t getSize() const
		{
			return(sBigNumber_.size());
		}

		inline ROperator compare(const BigNumber& bnCompareIn) const
		{

			size_t maxSize = std::max<size_t>(sBigNumber_.size(), bnCompareIn.getSize());
			
			BigNumber bnCompare(bnCompareIn);
			BigNumber bnCompareThis(*this);

			bnCompare.setSize(Side::Right, maxSize);
			bnCompareThis.setSize(Side::Right, maxSize);

			for (int idx = 0; idx < bnCompareThis.getSize(); ++idx) {
				if (bnCompareThis.getNumber()[idx] < bnCompare.getNumber()[idx]) {
					return(ROperator::Less);
				}
				if (bnCompareThis.getNumber()[idx] > bnCompare.getNumber()[idx]) {
					return(ROperator::Greater);
				}
			}

			return(ROperator::Equal);
		}

		inline void reset()
		{
			sBigNumber_.erase();
		}

		void ltrim()
		{
			size_t stopPos = sBigNumber_.find_first_not_of('0', 0);
			sBigNumber_.erase(0, stopPos);

			if (sBigNumber_.empty()) {
				sBigNumber_ = "0";
			}
		}
		void rtrim()
		{
			while (sBigNumber_.size() > 1) {  // not clear string
				rightrotate(sBigNumber_, 1);
				size_t stopPos = sBigNumber_.find_first_not_of('0', 0);
				if (stopPos == 0) {
					leftrotate(sBigNumber_, 1);
					break;
				}
				sBigNumber_.erase(0, 1);
			}
		}

		inline void incrementSize(Side side, size_t size)
		{
			setSize(side, getSize() + size);
		}
		void setSize(Side side, size_t size)
		{
			if (getSize() >= size) {	// It is not possible decrease size
				return;
			}

			if (side == Side::Right) {
				shiftRigth(size - getSize()); // increase size
				return;
			}

			shiftLeft(size - getSize()); // increase size
//			ltrim();
		}

		inline void shiftRigth(size_t size)
		{
			sBigNumber_.insert(0, size, '0');
		}

		inline void shiftLeft(size_t size)
		{
			sBigNumber_.insert(sBigNumber_.size(), size, '0');
		}


		inline void concatenate(const BigNumber& BigNumber)
		{
			sBigNumber_.append(BigNumber.getNumber());
		}

		inline BigNumber& at(std::size_t idx)
		{
			at_ = idx;
			return(*this);
		}


		inline BigNumber& operator=(int digit)
		{
			sBigNumber_[at_] = '0' + digit;

			return(*this);
		}
		inline void replaceNumber(const std::string& sBigNumber)
		{
			
			if (!validate(sBigNumber)) {
				std::stringstream error;
				error << "Invalid BigNumber: " << sBigNumber;
				throw(std::exception(error.str().c_str()));
			}

			sBigNumber_ = sBigNumber;
		}

	private:

		bool validate(const std::string& bigNumber) const
		{
			return (std::all_of(bigNumber.begin(), bigNumber.end(),
				[](char c)
				{ return (isdigit(c) != 0); }
			));

		}

		void leftrotate(std::string& s, size_t d)
		{
			std::rotate(s.begin(), s.begin() + d, s.end());
		}

		void rightrotate(std::string& s, size_t d)
		{
			leftrotate(s, s.length() - d);
		}

	private:
		std::string sBigNumber_;
		size_t at_ = 0;

	};



	//**************************************************************************************
	//*	
	//*		class MathBigNumber
	//*
	//*************************************************************************************

	
	class MathBigNumber
	{
	public:

		virtual ~MathBigNumber() = default;


		MathBigNumber(const MathBigNumber& mathBigNumber)
			:bigInteger_(mathBigNumber.bigInteger_), bigDecimal_(mathBigNumber.bigDecimal_), 
			 signal_(mathBigNumber.signal_)
		{

		}
		MathBigNumber(const MathBigNumber& mathBigNumber, Signal signal)
			:bigInteger_(mathBigNumber.bigInteger_), bigDecimal_(mathBigNumber.bigDecimal_),
			signal_(signal)
		{

		}


		explicit MathBigNumber(size_t size = 0)
			: bigInteger_(""), bigDecimal_(""), signal_(Signal::Positive)
		{
			getInteger().setSize(Side::Right, size);
		}

		explicit MathBigNumber(const BigNumber bnInteger,  BigNumber bnDecimal, Signal signal)
			: MathBigNumber(bnInteger.getNumber(), bnDecimal.getNumber(),signal)
		{
			
		}

		explicit MathBigNumber(const std::string& bigInteger,
			const std::string& bigDecimal, Signal signal)
			: bigInteger_(bigInteger), bigDecimal_(bigDecimal), signal_(signal)
		{
			if ((!validate(bigInteger)) ||
				(!validate(bigDecimal))) {
				std::stringstream error;
				error << "Invalid MathBigNumber: " << bigInteger << "," << bigDecimal ;
				throw(std::exception(error.str().c_str()));
			}
		}

		explicit MathBigNumber(const std::string& bigNumber)
			: bigInteger_("0"), bigDecimal_(""), signal_(Signal::Positive)
		{

			size_t signalPos = 0;

			if ((signalPos = bigNumber.find('-', 0)) != std::string::npos) {
				signal_ = Signal::Negative;
				signalPos = 1;
			}
			else {
				signalPos = 0;
			}


			size_t  decimalPos = bigNumber.find(".", signalPos);
			if (decimalPos != std::string::npos) {
				bigInteger_ = BigNumber(bigNumber.substr(signalPos, decimalPos - signalPos));
				bigDecimal_ = BigNumber(bigNumber.substr(decimalPos + 1, std::string::npos));
			}
			else {
				bigInteger_ = BigNumber(bigNumber.substr(signalPos, std::string::npos));
				bigDecimal_ = BigNumber("");
			}
		}

		const MathBigNumber& operator=(const MathBigNumber& mathBigNumber)
		{
			
			this->bigInteger_ = mathBigNumber.bigInteger_;
			this->bigDecimal_ = mathBigNumber.bigDecimal_;
			this->signal_ = mathBigNumber.signal_;

			return(*this);
		}


		void reset()
		{
			bigInteger_.reset();
			bigDecimal_.reset();
			signal_ = Signal::Positive;
		}

		inline Signal getSignal() const
		{
			return(signal_);
		}
		void setSignal(Signal signal)
		{
			signal_ = signal;
		}
		//void setPartition(Partition partition, const BigNumber& bigNumber)
		//{
		//	if (partition == Partition::Integer) {
		//		bigInteger_ = bigNumber;
		//		return;
		//	}
		//	bigDecimal_ = bigNumber;
		//}
		//inline const BigNumber& getPartition(Partition part) const
		//{
		//	if (part == Partition::Integer) {
		//		return(getInteger());
		//	}
		//	return(getDecimal());
		//}
		
		inline const BigNumber& getInteger() const
		{
			return(bigInteger_);
		}
		inline const BigNumber& getDecimal() const
		{
			return(bigDecimal_);
		}
		inline BigNumber& getInteger()
		{
			return(bigInteger_);
		}
		inline BigNumber& getDecimal()
		{
			return(bigDecimal_);
		}
		inline const std::string getNumber() const
		{
			std::string signal = signal_ == Signal::Negative ? "-" : "";
			std::string integer = bigInteger_.getNumber();
			std::string decimal = bigDecimal_.getNumber().size() > 0 ? "." + bigDecimal_.getNumber() : "";

			return(std::move(signal + integer + decimal));
		}

		void truncate(size_t precision)
		{
			if (bigDecimal_.getSize() > precision) {
				bigDecimal_.replaceNumber(bigDecimal_.getNumber().substr(0, precision));
			}
		}
		inline ROperator compare(const MathBigNumber& bnCompare) const
		{
			if (getSignal() != bnCompare.getSignal()) {
				if (signal_ == Signal::Negative) {
					return(ROperator::Less);
				}
				return(ROperator::Greater);
			}

			ROperator integerCmp = bigInteger_.compare(bnCompare.getInteger());
			if (integerCmp == ROperator::Equal) {
				return(bigDecimal_.compare(bnCompare.getDecimal()));
			}

			return(integerCmp);

		}
		MathBigNumber getMathBNRound(size_t precision)
		{
			if (bigDecimal_.getSize() < precision) {
				return(std::move(MathBigNumber(0)));
			}
			if (bigDecimal_.getNumber()[precision - 1] < '5') {
				return(std::move(MathBigNumber(0)));
			}

			BigNumber bnRound(0);
			bnRound.shiftRigth(precision - 1);
			bnRound.concatenate(BigNumber("1"));

			return(std::move(MathBigNumber(BigNumber("0"), bnRound, Signal::Positive)));

		}
	private:	
		bool validate(const std::string& bigNumber) const
		{
			return (std::all_of(bigNumber.begin(), bigNumber.end(),
				[](char c)
				{ return (c != '-' || c != '.'); }
			));

		}


	private:
		BigNumber bigInteger_;
		BigNumber bigDecimal_;
		Signal signal_ = Signal::Positive;



		size_t at_ = 0;

	};



}

#endif

