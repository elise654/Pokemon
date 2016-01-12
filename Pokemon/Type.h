#pragma once
#ifndef TYPE_H
#define TYPE_H
#include <string>
using namespace std;

namespace SoftwareLogic
{
	class Type
	{
		public:
				Type();
				~Type();
				Type(string typeName);
				void setWeakness(string weaknessTypeName);
				void setWeakness(string weaknessTypeName1, string weaknessTypeName2);
				void setStrength(string strengthTypeName);
				void setStrength(string strengthTypeName1, string strengthTypeName2);
				string getWeakness1() const;
				string getWeakness2() const;
				string getStrength1() const;
				string getStrength2() const;
				string getTypeName() const;
		private:
				string name;
				string weakness1;
				string weakness2;
				string strength1;
				string strength2;
	};


}

#endif