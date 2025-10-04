#pragma once

#ifndef _BNNOTATION_H_
#define _BNNOTATION_H_

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





namespace BigNum
{
	//**************************************************************************************
	//*
	//*		Interface IBNNotationMath
	//*
	//*************************************************************************************

	class IBNNotationMath
	{
	public:
		using Pointer = std::unique_ptr<IBNNotationMath>;
		virtual ~IBNNotationMath() = default;


	};
}
namespace BigNum
{
	enum class NotationType
	{
		digit = 0,
		add = 1,
		subtract = 2,
		multiply = 3,
		divide = 4,
		module = 5,

	};


	//**************************************************************************************
	//*	
	//*		class IceServer
	//*
	//*************************************************************************************
	class BNNotationMath
		: public IBNNotationMath
	{
	public:
		using Pointer = std::shared_ptr<BNNotationMath>;
		using PairPostFix = std::pair<NotationType, std::string>;
		using PostFixStack = std::stack<PairPostFix>;
		using StackWork = std::stack<std::string>;

		template<typename ...Args>
		Pointer static create(Args &&...arg)
		{
			struct EnaleMakeShared
				: public BNNotationMath
			{
				EnaleMakeShared(Args &&...arg)
					: BNNotationMath(std::forward<Args>(arg)...)
				{}
			};
			Pointer result(std::make_unique<EnaleMakeShared>(std::forward<Args>(arg)...));
			return(std::move(result));
		}
		virtual ~BNNotationMath() = default;


		BNNotationMath(const BNNotationMath&) = delete;
		BNNotationMath(BNNotationMath&&) = delete;
		const BNNotationMath& operator=(const BNNotationMath&) = delete;



		void convertToPostfix()
		{
			StackWork sWworkStack;

			auto pushPostStack = [this](const std::string token)
			{
				switch (token[0]) {
					case '+':
						sPostfixStack_.push(std::make_pair(NotationType::add, token));
						break;
					case '-':
						sPostfixStack_.push(std::make_pair(NotationType::subtract, token));
						break;
					case '*':
						sPostfixStack_.push(std::make_pair(NotationType::multiply, token));
						break;
					case '/':
						sPostfixStack_.push(std::make_pair(NotationType::divide, token));
						break;
					case '%':
						sPostfixStack_.push(std::make_pair(NotationType::module, token));
						break;
				}
				
			};

			for (size_t idx = 0; idx < tokens_.size(); ++idx) {
				if (symbolIsNumber(tokens_[idx])) {
					sPostfixStack_.push(std::make_pair(NotationType::digit, tokens_[idx]));
				}
				if (tokens_[idx] == "(") {
					sWworkStack.push(tokens_[idx]);
				}
				if (tokens_[idx] == ")") {
					while (!sWworkStack.empty() && sWworkStack.top() != "(") {
						pushPostStack(sWworkStack.top());
						sWworkStack.pop();
					}
					sWworkStack.pop();
				}
				if (isOperator(tokens_[idx]) == true) {
					while ((!sWworkStack.empty()) &&
						(priority(sWworkStack.top()) >= priority(tokens_[idx]))) {
						pushPostStack(sWworkStack.top());
						sWworkStack.pop();
					}
					sWworkStack.push(tokens_[idx]);
				}
			}

			//pop any remaining operators from the stack and insert to outputlist
			while (!sWworkStack.empty()) {
				pushPostStack(sWworkStack.top());
				sWworkStack.pop();
			}


			reverseStack(sPostfixStack_);

		}


		PostFixStack& getPostFixStack()
		{
			return(sPostfixStack_);
		}
	private:
		explicit BNNotationMath(const std::string& infix)
			: infix_(infix)
		{
			parser();
		}

		void parser()
		{
			for (int idx = 0; idx < infix_.size(); ++idx) {
				int start = idx;
				bool hasDigits = false;
				int qty = 0;

				while (std::isdigit(infix_[idx])) {
					hasDigits = true;
					++qty;
					if (infix_[++idx] == '.') {
						++idx;
						++qty;
					}
				}
				const std::string& token = infix_.substr(start, std::max<int>(1, qty));

				if (token != " ") {
					tokens_.push_back(token);
				}

				if (hasDigits) {
					--idx;
				}
			}
		}
		template<typename TYPE>
		void reverseStack(std::stack<TYPE>& oneStack)
		{
			std::stack<TYPE> reverseStack;
			while (!oneStack.empty()) {
				reverseStack.push(std::move(oneStack.top()));
				oneStack.pop();
			}
			oneStack = std::move(reverseStack);
		}
		bool symbolIsNumber(const std::string& symbol)
		{
			bool isNumber = false;
			for (size_t idx = 0; idx < symbol.size(); ++idx) {
				if (!isdigit(symbol[idx])) {
					isNumber = false;
				}
				else {
					isNumber = true;
				}
			}
			return(isNumber);
		}

		int priority(const std::string& oper)
		{
			switch (oper.c_str()[0]) {
				case '^':
					return (3);
				case '*':
				case '/':
				case '%':
					return (2);
				case '+':
				case '-':
					return (1);
			}

			return(0);
		}

		bool isOperator(const std::string& c)
		{
			return (c == "+" || c == "-" || c == "*" || c == "/" || c == "%");
		}


	private:
		const std::string infix_;
		std::vector<std::string> tokens_;
		PostFixStack sPostfixStack_;


	};
}


#endif // !_NEWCLASS_H_

