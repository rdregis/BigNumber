#pragma once

#ifndef _BNRELATOPERATOR_H_
#define _BNRELATOPERATOR_H_

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

#include "BigNumber.h"
#include "BNExecutor.h"




namespace BigNum
{
	//**************************************************************************************
	//*
	//*		Interface  IBNOperatorRelat
	//*
	//*************************************************************************************

	class IBNOperatorRelat
	{
	public:
		using Pointer = std::unique_ptr<IBNOperatorRelat>;
		virtual ~IBNOperatorRelat() = default;


	};
}
namespace BigNum

{

	//**************************************************************************************
	//*	
	//*		class BNOperatorRelat
	//*
	//*************************************************************************************
	class BNOperatorRelat
		: public IBNOperatorRelat
	{
	public:
		using Pointer = std::unique_ptr<BNOperatorRelat>;

		template<typename ...Args>
		Pointer static create(Args &&...arg)
		{
			struct EnaleMakeShared
				: public BNOperatorRelat
			{
				EnaleMakeShared(Args &&...arg)
					: BNOperatorRelat(std::forward<Args>(arg)...)
				{}
			};
			Pointer result(std::make_unique<EnaleMakeShared>(std::forward<Args>(arg)...));
			return(std::move(result));
		}
		virtual ~BNOperatorRelat() = default;


		BNOperatorRelat(const BNOperatorRelat&) = delete;
		BNOperatorRelat(BNOperatorRelat&&) = delete;
		const BNOperatorRelat& operator=(const BNOperatorRelat&) = delete;

		ROperator execute(MathBigNumber& bn1, MathBigNumber& bn2)
		{

			BNExecutor::Pointer bnExecutor = BNExecutor::create();

			MathBigNumber bnRstSub = bn1 - bn2;

			if (bnRstSub.getNumber() == "0") {
				return(ROperator::Equal);
			}
			if (bnRstSub.getNumber() < "0") {
				return(ROperator::Less);
			}
			return(ROperator::Greater);
		}
	private:
		explicit BNOperatorRelat()
		{
		}


	private:


	};

	

}


#endif // !_NEWCLASS_H_

