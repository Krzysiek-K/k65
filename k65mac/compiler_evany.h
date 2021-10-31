
// this file is included inside EvalAny class

#define TT(at,bt)	(a.type==ET_##at && b.type==ET_##bt)


EvalAny operator +(const EvalAny &b) const
{
	const EvalAny &a = *this;
	if(TT(NUMBER,NUMBER)) return EvalAny(a.value_f+b.value_f);
	if(a.type==ET_STRING || b.type==ET_STRING)
		return a.GetString() + b.GetString();
	Error("Can't add %s and %s",a,b);
	return EvalAny();
}

EvalAny operator -(const EvalAny &b) const
{
	const EvalAny &a = *this;
	if(TT(NUMBER,NUMBER)) return EvalAny(a.value_f-b.value_f);
	Error("Can't subtract %s from %s",b,a);
	return EvalAny();
}

EvalAny operator -() const
{
	if(type==ET_NUMBER) return EvalAny(-value_f);
	Error("Can't negate %s",*this);
	return EvalAny();
}

EvalAny operator *(const EvalAny &b) const
{
	const EvalAny &a = *this;
	if(TT(NUMBER,NUMBER)) return EvalAny(a.value_f*b.value_f);
	Error("Can't multiply %s by %s",a,b);
	return EvalAny();
}

EvalAny operator /(const EvalAny &b) const
{
	const EvalAny &a = *this;
	if(TT(NUMBER,NUMBER) && b.value_f!=0) return EvalAny(a.value_f/b.value_f);
	Error("Can't divide %s by %s",a,b);
	return EvalAny();
}

bool operator ==(const EvalAny &b) const
{
	const EvalAny &a = *this;
	if(a.type!=b.type) return false;
	if(TT(NUMBER,NUMBER)) return a.value_f == b.value_f;
	if(TT(STRING,STRING)) return a.value_s == b.value_s;
	if(TT(SECTION,SECTION)) return a.value_i == b.value_i;
	Error("Can't compare %s and %s",b,a);
	return false;
}

bool operator <(const EvalAny &b) const
{
	const EvalAny &a = *this;
	if(TT(NUMBER,NUMBER)) return a.value_f < b.value_f;
	if(TT(STRING,STRING)) return a.value_s < b.value_s;
	Error("Can't compare %s and %s",b,a);
	return false;
}

bool operator !=(const EvalAny &b) const	{ return !(*this==b);	}
bool operator >(const EvalAny &b) const		{ return  (b<*this);	}
bool operator <=(const EvalAny &b) const	{ return !(b<*this);	}
bool operator >=(const EvalAny &b) const	{ return !(*this<b);	}





#undef TT
