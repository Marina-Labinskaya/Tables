#include "polynom.h"

Monom::Monom(double coeff, int deg)
{
	k = coeff;
	degree = deg;
	if (!deg_is_correct())
		throw std::logic_error("Invalid degree");
}

Monom::Monom(const Monom& a)
{
	k = a.k;
	degree = a.degree;
}

bool Monom::deg_is_correct()
{
	if ((x_degree() <= MAX_DEG) && (y_degree() <= MAX_DEG) && (z_degree() <= MAX_DEG))
		return true;
	else
		return false;
}

bool Monom:: operator ==(const Monom& m)
{
	if ((m.degree == degree) && (m.k == k))
		return true;
	else
		return false;
}

bool Monom:: operator !=(const Monom& m)
{
	return !(*this == m);
}

Monom Monom::operator+(const Monom& a)
{
	Monom res;
	if (a.degree == degree)
	{
		res.k = a.k + k;
		res.degree = degree;
	}
	else
		throw std::logic_error("It is not a monom");
	return res;
}

Monom Monom::operator* (const Monom& a)
{
	Monom res;
	if ((x_degree() + a.x_degree() <= MAX_DEG) && (y_degree() + a.y_degree() <= MAX_DEG) && \
		(z_degree() + a.z_degree() <= MAX_DEG))
	{
		res.k = a.k * k;
		res.degree = a.degree + degree;
	}
	else
		throw std::logic_error("Invalid resulting degree");
	return res;
}

Polynom Monom::operator* (const Polynom& pol)
{
	Polynom res;
	Polynom::iterator it1 = pol.begin();
	Polynom::iterator it2 = res.begin();
	while (it1 != pol.end())
	{
		res.insert((*this) * (it1->data), it2.get_it());
		++it1;
		++it2;
		if (!deg_is_correct())
			throw std::logic_error("Invalid resulting degree");
	}
	return res;
}

Polynom Polynom::operator+ (const Polynom& pol)
{
	Polynom res;

	Polynom::iterator it1 = begin();
	Polynom::iterator it2 = pol.begin();
	Polynom::iterator it3 = res.begin();

	while ((it1 != end()) && (it2 != pol.end()))
	{
		if ((it1->data.degree) < (it2->data.degree))
		{
			res.insert(it1->data, it3.get_it());
			++it1;
			++it3;
		}
		else if ((it2->data.degree) < (it1->data.degree))
		{
			res.insert(it2->data, it3.get_it());
			++it2;
			++it3;
		}
		else if ((it2->data.degree) == (it1->data.degree))
		{
			res.insert((it1->data + it2->data), it3.get_it());
			++it1;
			++it2;
			++it3;
		}
	}
	if (it1 == end())
	{
		while (it2 != pol.end())
		{
			res.insert(it2->data, it3.get_it());
			++it2;
			++it3;
		}
	}
	else
	{
		while (it1 != end())
		{
			res.insert(it1->data, it3.get_it());
			++it1;
			++it3;
		}
	}
	return res;
}

Polynom Polynom::operator* (const Polynom& pol)
{
	Polynom res;
	Polynom pol2(res);
	Polynom::iterator it1 = begin();
	while (it1 != end())
	{
		pol2 = (it1->data) * pol;
		res = res + pol2;
		++it1;
	}
	return res;
}