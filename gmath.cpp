#include "gmath.h"


// ���� ������ ����� �ʱ�ȭ
double GLine::Precision = 1.0e-7;
double GPlane::Precision = 1.0e-7;
double GPos3::Precision = 1.0e-7;
double GVec3::Precision = 1.0e-7;


////////////////////////////////////////////////////////////

/*!
*	\brief ����Ʈ ������
*	
*	\param x x-��ǥ
*	\param y y-��ǥ
*	\param z z-��ǥ
*/
GVec3::GVec3(double x, double y, double z)
{
	V[0] = x;
	V[1] = y;
	V[2] = z;
}

/*!
*	\brief	���������
*
*	\param cpy ����� ��ü
*/
GVec3::GVec3(const GVec3 &cpy)
{
	V[0] = cpy.V[0];
	V[1] = cpy.V[1];
	V[2] = cpy.V[2];
}

/*!
*	\brief �Ҹ���
*/
GVec3::~GVec3()
{
}

/*!
*	\brief ���Կ�����
*
*	\param rhs ������ �ǿ�����
*
*	\return ���Ե� �ڽ�
*/
GVec3 &GVec3::operator =(const GVec3 &rhs)
{
	V[0] = rhs.V[0];
	V[1] = rhs.V[1];
	V[2] = rhs.V[2];
	return *this;
}

/*!
*	\brief ���մ��Կ�����
*
*	\param rhs ������ �ǿ�����
*
*	\return ������ ���Ե� �ڽ�
*/
GVec3 &GVec3::operator +=(const GVec3 &rhs)
{
	V[0] += rhs.V[0];
	V[1] += rhs.V[1];
	V[2] += rhs.V[2];
	return *this;
}

/*!
*	\brief ���մ��Կ�����
*
*	\param rhs ������ �ǿ�����
*
*	\return ������ ���Ե� �ڽ�
*/
GVec3 &GVec3::operator -=(const GVec3 &rhs)
{
	V[0] -= rhs.V[0];
	V[1] -= rhs.V[1];
	V[2] -= rhs.V[2];
	return *this;
}

/*!
*	\brief ���մ��Կ�����
*
*	\param s ���� ���
*
*	\return ������ ���Ե� �ڽ�
*/
GVec3 &GVec3::operator *=(const double &s)
{
	V[0] *= s;
	V[1] *= s;
	V[2] *= s;
	return *this;
}

/*!
*	\brief ���մ��Կ�����
*
*	\param s ���� ���
*
*	\return ������ ���Ե� �ڽ�
*/
GVec3 &GVec3::operator /=(const double &s)
{
	V[0] /= s;
	V[1] /= s;
	V[2] /= s;
	return *this;
}

/*!
*	\brief ���մ��Կ�����
*
*	\param rhs ������ ������ �ǿ�����
*
*	\return ������ ���Ե� �ڽ�
*/
GVec3 &GVec3::operator ^=(const GVec3 &rhs)
{
	double x = V[0], y = V[1], z = V[2];
	V[0] = y * rhs.V[2] - z * rhs.V[1];
	V[1] = z * rhs.V[0] - x * rhs.V[2];
	V[2] = x * rhs.V[1] - y * rhs.V[0];
	return *this;
}

/*!
*	\brief ���׿�����
*
*	\return �ݴ��ȣ�� ���� ��ü
*/
GVec3 GVec3::operator +() const
{
	return *this;
}

/*!
*	\brief ���׿�����
*
*	\return �ݴ��ȣ�� ���� ��ü
*/
GVec3 GVec3::operator -() const
{
	return *this * -1;
}

/*!
*	\brief ���������(+)
*
*	\param lhs ���� �ǿ�����
*	\param rhs ������ �ǿ�����
*
*	\return ������ ����� ��ȯ
*/ 
GVec3 operator +(const GVec3 &lhs, const GVec3 &rhs)
{
	return GVec3(lhs.V[0] + rhs.V[0], lhs.V[1] + rhs.V[1], lhs.V[2] + rhs.V[2]);
}

/*!
*	\brief ���������(-)
*
*	\param lhs ���� �ǿ�����
*	\param rhs ������ �ǿ�����
*
*	\return ������ ����� ��ȯ
*/ 
GVec3 operator -(const GVec3 &lhs, const GVec3 &rhs)
{
	return GVec3(lhs.V[0] - rhs.V[0], lhs.V[1] - rhs.V[1], lhs.V[2] - rhs.V[2]);
}

/*!
*	\brief ����������(*)
*
*	\param lhs ���� �ǿ�����
*	\param rhs ������ �ǿ�����
*
*	\return ������ ����� ��ȯ
*/
double operator *(const GVec3 &lhs, const GVec3 &rhs)
{
	return lhs.V[0] * rhs.V[0] + lhs.V[1] * rhs.V[1] + lhs.V[2] * rhs.V[2];
}

/*!
*	\brief ���������(/)
*
*	\param s ���� ���
*	\return ������ ����� ��ȯ
*/
GVec3 operator /(const GVec3 &lhs, const double &s)
{
	return GVec3(lhs.V[0] / s, lhs.V[1] / s, lhs.V[2] / s);
}

/*!
*	\brief ����������(^)
*
*	\param lhs ���� �ǿ�����
*	\param rhs ������ �ǿ�����
*
*	\return ������ ����� ��ȯ
*/
GVec3 operator ^(const GVec3 &lhs, const GVec3 &rhs)
{
	return GVec3(lhs.V[1] * rhs.V[2] - lhs.V[2] * rhs.V[1], lhs.V[2] * rhs.V[0] - lhs.V[0] * rhs.V[2], lhs.V[0] * rhs.V[1] - lhs.V[1] * rhs.V[0]);
}

/*!
*	\brief ��ȣ������
*
*	\param lhs ���� �ǿ�����
*	\param rhs ������ �ǿ�����
*
*	\return �� ����� ��ȯ
*/
bool operator ==(const GVec3 &lhs, const GVec3 &rhs)
{
	double error = GVec3::Precision;
	return (EQ(lhs.V[0], rhs.V[0], error) && EQ(lhs.V[1], rhs.V[1], error) && EQ(lhs.V[2], rhs.V[2], error));
}

/*!
*	\brief �ε�ȣ������
*
*	\param lhs ���� �ǿ�����
*	\param rhs ������ �ǿ�����
*
*	\return �� ����� ��ȯ
*/
bool operator !=(const GVec3 &lhs, const GVec3 &rhs)
{
	double error = GVec3::Precision;
	return (!EQ(lhs.V[0], rhs.V[0], error) || !EQ(lhs.V[1], rhs.V[1], error) || !EQ(lhs.V[2], rhs.V[2], error));
}

/*!
*	\brief ÷�ڿ�����([])
*
*	\param idx ÷��
*	\param ������ \a idx��° ���Ҹ� ��ȯ
*/
double &GVec3::operator [](const int &idx)
{
	assert(idx >= 0 && idx < 3);
	return V[idx];
}

/*!
*	\brief �����ü�� ���� ÷�ڿ�����([])
*
*	\param idx ÷��
*	\param ������ \a idx��° ���Ҹ� ��ȯ
*/
const double &GVec3::operator [](const int &idx) const
{
	assert(idx >= 0 && idx < 3);
	return V[idx];
}

/*!
*	\brief ������ ��ǥ�� ����
*
*	\param x x-��ǥ
*	\param y y-��ǥ
*	\param z z-��ǥ
*/
GVec3 &GVec3::Set(const double &x, const double &y, const double &z)
{
	V[0] = x;
	V[1] = y;
	V[2] = z;
	return *this;
}

/*!
*	\brief ���͸� �����Ͽ� �������ͷ� ��ȯ
*
*	\return ��ȯ�� �ڽ��� ��ȯ
*/
GVec3 &GVec3::Normalize()
{
	double len = norm(*this);
	if (EQ_ZERO(len, Precision))
		return *this;
	V[0] /= len;
	V[1] /= len;
	V[2] /= len;
	return *this;
}

/*!
*	\brief ��ȣ �� �ε�ȣ �������� ������ �Ѱ� ����
*
*	\param error ������ �Ѱ�
*/
void GVec3::SetPrecision(double error)
{
	Precision = error;
}

/*!
*	\brief ������ ������ �Ѱ踦 ��ȯ
*
*	\return ������ ������ �Ѱ�
*/
double GVec3::GetPrecision()
{
	return Precision;
}

/*!
*	\brief ���������(*)
*
*	\param lhs ���� �ǿ�����
*	\param s ������ �ǿ�����
*
*	\return ������ ����� ��ȯ
*/
GVec3 operator *(const GVec3 &lhs, const double &s)
{
	GVec3 ret(lhs);
	ret *= s;
	return ret;
}

/*!
*	\brief ���������(*)
*
*	\param s ���� �ǿ�����
*	\param lhs ������ �ǿ�����
*
*	\return ������ ����� ��ȯ
*/
GVec3 operator *(const double &s, const GVec3 &rhs)
{
	GVec3 ret(rhs);
	ret *= s;
	return ret;
}

/*!
*	\brief ��¿�����(<<)
*
*	\param os ��½�Ʈ��
*	\param v ����� ����
*
*	\return \a v�� ��µ� ��Ʈ���� ��ȯ
*/
std::ostream &operator <<(std::ostream &os, const GVec3 &v)
{
	os << "(" << std::setw(10) << v.V[0] << ", " << std::setw(10) << v.V[1] << ", " << std::setw(10) << v.V[2] << ")";
	return os;
}

/*!
*	\brief �Է¿�����(>>)
*
*	\param is �Է½�Ʈ��
*	\param v �Է°��� ����� ����
*
*	\return �Է°��� ���ŵ� �Է½�Ʈ��
*/
std::istream &operator >>(std::istream &is, GVec3 &v)
{
	is >> v.V[0] >> v.V[1] >> v.V[2];
	return is;
}

/*!
*	\brief ���� v�� ���� w�� �翵��Ų ���͸� ���Ѵ�.
*
*	\param v ����.
*	\param w ����.
*
*	\return ���� v�� ���� w�� �翵��Ų ���͸� ��ȯ�Ѵ�.
*/
GVec3 proj(const GVec3 &v, const GVec3 &w)
{
	return (v * w / (w.V[0] * w.V[0] + w.V[1] * w.V[1] + w.V[2] * w.V[2])) * w;
}

/*!
*	\brief ���� v�� ������ ���͸� ���Ѵ�.
*
*	\param v ����
*
*	\return ���� v�� ������ ���͸� ���Ͽ� ��ȯ�Ѵ�.
*/
GVec3 ortho(const GVec3 &v)
{
	GVec3 ret;

	double min_val = MIN(MIN(v[0], v[1]), v[2]);
	if (min_val == v[0])
		ret.Set(0.0, -v[2], v[1]);
	
	if (min_val == v[1])
		ret.Set(v[2], 0.0, -v[0]);

	if (min_val == v[2])
		ret.Set(-v[1], v[0], 0.0);

	return ret;
}

/*!
*	\brief ���� v, w�� ���̺����� ���̸� ���Ѵ�.
*
*	\param v ����.
*	\param w ����.
*
*	\return  ���� \a v, \a w�� ���̺����� ����
*/
double dist(const GVec3 &v, const GVec3 &w)
{
	return norm(v - w);
}

/*!
*	\brief ���� u, v, w�� ��Ľ��� ����Ѵ�.
*
*	\param u ����.
*	\param v ����.
*	\param w ����.
*
*	\return  ���� u, v, w�� ��Ľ��� ���� ��ȯ�Ѵ�.
*/
double det(const GVec3 &u, const GVec3 &v, const GVec3 &w)
{
	return (u[0] * v[1] * w[2] + u[1] * v[2] * w[0] + u[2] * v[0] * w[1]) - (w[0] * v[1] * u[2] + v[0] * u[1] * w[2] + u[0] * w[1] * v[2]);
}

/*!
*	\brief ���� v�� ũ�⸦ ���Ѵ�.
*
*	\param v ����
*
*	\return ���� \a v�� ũ��
*/ 
double norm(const GVec3 &v)
{
	return SQRT(SQR(v.V[0]) + SQR(v.V[1]) + SQR(v.V[2]));
}

/*!
*	\brief �� ���� ������ ���̰��� ���Ѵ�.
*	\warning 0 <= ���̰� <= 180
*
*	\param v ���� ����
*	\param w �� ����
*	\param radian ������ ����(true: radian, false: degree)
*
*	\return ���� \a v���� ���� \a w������ ���̰�(����, ���� �������)
*/
double angle(const GVec3 &v, const GVec3 &w, bool radian)
{
	GVec3 p(v);
	GVec3 q(w);
	double cs, sn, theta;

	p.Normalize();
	q.Normalize();

	cs = p * q;
	sn = norm(p ^ q);

	theta = radian ? atan2(sn, cs) : RAD2DEG(atan2(sn, cs));
	return theta;
}

/*!
*	\brief �� ���� ������ ���̰��� ���Ѵ�.
*	\warning 0 <= ���̰� <= 360
*
*	\param v ���� ����
*	\param w �� ����
*	\param up ���� ����
*	\param radian ������ ����(true: radian, false: degree)
*
*	\return ���� \a v���� ���� \a w������ ���̰�(���� ���͸� ���������� �� �ð����)
*/
double angle(const GVec3 &v, const GVec3 &w, const GVec3 &up, bool radian)
{
	GVec3 p(v);
	GVec3 q(w);
	double cs, sn, theta;

	p.Normalize();
	q.Normalize();
	GVec3 r = p ^ q;

	cs = p * q;
	sn = norm(r);

	theta = atan2(sn, cs);
	if (r * up < 0.0)	
		theta = 2 * M_PI - theta;
	
	theta = radian ? theta : RAD2DEG(theta);
	return theta;
}


/////////////////////////////////////////////////////////////////////

/*!
*	\brief ����Ʈ ������
*	
*	\param x x-��ǥ
*	\param y y-��ǥ
*	\param z z-��ǥ
*/
GPos3::GPos3(double x, double y, double z)
{
	V[0] = x;
	V[1] = y;
	V[2] = z;
}

/*!
*	\brief ���������
*
*	\param cpy ����� ��ü
*
*	\return ����� �ڽ��� ��ȯ
*/
GPos3::GPos3(const GPos3 &cpy)
{
	V[0] = cpy.V[0];
	V[1] = cpy.V[1];
	V[2] = cpy.V[2];
}

/*!
*	\brief  �Ҹ���
*/
GPos3::~GPos3()
{
}

/*!
*	\brief ���Կ�����
*
*	\param rhs ������ �ǿ�����
*
*	\return ���Ե� �ڽ��� ��ȯ
*/
GPos3 &GPos3::operator =(const GPos3 &rhs)
{
	V[0] = rhs.V[0];
	V[1] = rhs.V[1];
	V[2] = rhs.V[2];
	return *this;
}

/*!
*	\brief ���մ��Կ�����
*
*	\param rhs ������ �ǿ�����
*
*	\return ������ ���Ե� �ڽ�
*/
GPos3 &GPos3::operator +=(const GVec3 &rhs)
{
	V[0] += rhs.V[0];
	V[1] += rhs.V[1];
	V[2] += rhs.V[2];
	return *this;
}

/*!
*	\brief ���������(-)
*
*	\param lhs ���� �ǿ�����
*	\param rhs ������ �ǿ�����
*
*	\return ������ ���(����)�� ��ȯ
*/
GVec3 operator -(const GPos3 &lhs, const GPos3 &rhs)
{
	return GVec3(lhs.V[0] - rhs.V[0], lhs.V[1] - rhs.V[1], lhs.V[2] - rhs.V[2]);
}

/*!
*	\brief ���������(-)
*
*	\param lhs ���� �ǿ�����(����Ʈ)
*	\param rhs ������ �ǿ�����(����)
*
*	\return ������ ���(����Ʈ)�� ��ȯ
*/
GPos3 operator -(const GPos3 &lhs, const GVec3 &rhs)
{
	return GPos3(lhs.V[0] - rhs[0], lhs.V[1] - rhs[1], lhs.V[2] - rhs[2]);
}

/*!
*	\brief ���������(+)
*
*	\param lhs ���� �ǿ�����(����Ʈ)
*	\param rhs ������ �ǿ�����(����)
*
*	\return ������ ���(����Ʈ)�� ��ȯ
*/
GPos3 operator +(const GPos3 &lhs, const GVec3 &rhs)
{
	return GPos3(lhs.V[0] + rhs[0], lhs.V[1] + rhs[1], lhs.V[2] + rhs[2]);
}

/*!
*	\brief ���������(+)
*
*	\param lhs ���� �ǿ�����(����)
*	\param rhs ������ �ǿ�����(����Ʈ)

*
*	\return ������ ���(����Ʈ)�� ��ȯ
*/
GPos3 operator +(const GVec3 &lhs, const GPos3 &rhs)
{
	return GPos3(lhs.V[0] + rhs[0], lhs.V[1] + rhs[1], lhs.V[2] + rhs[2]);
}

/*!
*	\brief ��ȣ������
*
*	\param lhs ���� �ǿ�����
*	\param rhs ������ �ǿ�����
*
*	\return �񱳰���� ��ȯ
*/
bool operator ==(const GPos3 &lhs, const GPos3 &rhs)
{
	double error = GPos3::Precision;
	return (EQ(lhs.V[0], rhs.V[0], error) && EQ(lhs.V[1], rhs.V[1], error) && EQ(lhs.V[2], rhs.V[2], error));
}

/*!
*	\brief �ε�ȣ������
*
*	\param lhs ���� �ǿ�����
*	\param rhs ������ �ǿ�����
*
*	\return �񱳰���� ��ȯ
*/
bool operator !=(const GPos3 &lhs, const GPos3 &rhs)
{
	double error = GPos3::Precision;
	return (!EQ(lhs.V[0], rhs.V[0], error) || !EQ(lhs.V[1], rhs.V[1], error) || !EQ(lhs.V[2], rhs.V[2], error));
}

/*!
*	\brief ÷�ڿ�����([])
*
*	\param idx ÷��
*
*	\return \a idx ��° ���Ҹ� ��ȯ
*/
double &GPos3::operator [](const int &idx)
{
	assert(idx >= 0 && idx < 3);
	return V[idx];
}

/*!
*	\brief �����ü�� ÷�ڿ�����([])
*
*	\param idx ÷��
*
*	\return \a idx ��° ���Ҹ� ��ȯ
*/
const double &GPos3::operator [](const int &idx) const
{
	assert(idx >= 0 && idx < 3);
	return V[idx];
}

/*!
*	\brief ����Ʈ�� ��ǥ�� �����Ѵ�.
*
*	\param x x-��ǥ
*	\param y y-��ǥ
*	\param z z-��ǥ
*
*	\return ������ �ڽ��� ��ȯ
*/
GPos3 &GPos3::Set(const double &x, const double &y, const double &z)
{
	V[0] = x;
	V[1] = y;
	V[2] = z;
	return *this;
}

/*!
*	\brief ��ȣ �� �ε�ȣ �������� ������ �Ѱ� ����
*
*	\param error ������ �Ѱ�
*/
void GPos3::SetPrecision(double error)
{
	Precision = error;
}

/*!
*	\brief ������ ������ �Ѱ踦 ��ȯ
*
*	\return ������ ������ �Ѱ�
*/
double GPos3::GetPrecision()
{
	return Precision;
}

/*!
*	\brief ��¿�����(<<)
*
*	\param os ��½�Ʈ��
*	\param p ����� ��ü
*
*	\return ��µ� ��Ʈ�� ��ü�� ��ȯ
*/
std::ostream &operator <<(std::ostream &os, const GPos3 &p)
{
	os << "(" << std::setw(5) << p.V[0] << ", " << std::setw(5) << p.V[1] << ", " << std::setw(5) << p.V[2] << ")";
	return os;
}

/*!
*	\brief �Է¿�����(>>)
*
*	\param is �Է½�Ʈ��
*	\param v �Է°��� ����� ����
*
*	\return �Է°��� ���ŵ� �Է½�Ʈ��
*/
std::istream &operator >>(std::istream &is, GPos3 &p)
{
	is >> p.V[0] >> p.V[1] >> p.V[2];
	return is;
}

/*!
*	\brief �� \a p�� ���̸� ���Ѵ�.
*
*	\param p ��
*
*	\return �� \a p�� ����.
*/
double norm(const GPos3 &p)
{
	return SQRT(SQR(p.V[0]) + SQR(p.V[1]) + SQR(p.V[2]));
}

/*!
*	\brief �� \a p���� �� \a q������ �Ÿ��� ���Ѵ�.
*
*	\param p ��
*	\param q ��
*
*	\return �� \a p���� �� \a q������ �Ÿ�
*/
double dist(const GPos3 &p, const GPos3 &q)
{
	return SQRT(SQR(p.V[0] - q.V[0]) + SQR(p.V[1] - q.V[1]) + SQR(p.V[2] - q.V[2]));
}

/*!
*	\brief �� \a p���� �� \a q������ �Ÿ��� ������ ���Ѵ�.
*
*	\param p ��
*	\param q ��
*
*	\return �� \a p���� �� \a q������ �Ÿ�
*/
double dist_sq(const GPos3 &p, const GPos3 &q)
{
	return (SQR(p.V[0] - q.V[0]) + SQR(p.V[1] - q.V[1]) + SQR(p.V[2] - q.V[2]));
}

/*!
*	\brief �� pt�� ��ǥ�� �������·� ��ȯ�Ѵ�.
*
*	\param pt 3���� ������ ��
*
*	\return pt�� 3���� ���� ǥ��
*/
GVec3 cast_GVec3(const GPos3 &pt)
{
	return GVec3(pt[0], pt[1], pt[2]);
}

/*!
*	\brief �� p�� ��ǥ�� �־��� �ڸ�������(�ݿø��Ͽ�) ��Ÿ��
*
*	\param p 3���� ������ ��
*
*	\return �ݿø��� ���� ǥ��
*/
GPos3 round_off(const GPos3 &p, int place)
{
	double a = pow(10.0, -place);
	double x = ((int)(p[0] * a + 0.5)) / a;
	double y = ((int)(p[1] * a + 0.5)) / a;
	double z = ((int)(p[2] * a + 0.5)) / a;

	return GPos3(x, y, z);
}

/*!
*	\brief ���� v�� ��ǥ�� ����Ʈ ���·� ��ȯ
*
*	\param v 3���� ������ ����
*
*	\return v�� ��ǥ�� ����Ʈ ���·� ��ȯ
*/
GPos3 cast_pt3(const GVec3 &v)
{
	return GPos3(v[0], v[1], v[2]);
}

/*!
*	\brief ������ affine combination�� ���Ѵ�
*
*	\param N ���� ����
*	\param alpha0 ���
*	\param p0 ù ��° ��
*	\param alpha1 ���
*	\param p1 ù ��° ��
*
*	\return ������ affine combination�� ��� (alpha0 * p0 + alpha1 * p1 + ... + alpha_n-1 * p_n-1)
*/
GPos3 affine_sum(int N, ...)
{
	GPos3 ret;

	va_list ap;
	va_start(ap, N);
	for (int i = 0; i < N; ++i)
	{
		double alpha = va_arg(ap, double);
		GPos3 p = va_arg(ap, GPos3);

		ret[0] = ret[0] + alpha * p[0];
		ret[1] = ret[1] + alpha * p[1];
		ret[2] = ret[2] + alpha * p[2];
	}
	va_end(ap);

	return ret;
}

/*!
*	\brief ������ affine combination�� ���Ѵ�
*
*	\param Points ���� �迭�� ���� ������
*	\param Weights combination�� �����
*	\param Size ���� ���� (Points, Weights �迭�� ũ��)
*
*	\return ������ affine combination�� ��� (= Point[0] * Weight[0] + Points[1] * Weight[1] + ... + Points[Size-1] * Weight[Size-1])
*/
GPos3 affine_sum(GPos3 *Points, double *Weights, const int Size)
{
	GPos3 ret;
	for (int i = 0; i < Size; i++)
	{	
		ret.V[0] += Points[i][0] * Weights[i];
		ret.V[1] += Points[i][1] * Weights[i];
		ret.V[2] += Points[i][2] * Weights[i];
	}
	return ret;
}

///////////////////////////////////////////////////////////
/*!
*	\brief �������� �� ���� �������� ������ �����ϴ� ������.
*	
*	\param _p �������� �� ��
*	\param _v ������ ���� ����.
*/
GLine::GLine(const GPos3 &_p, const GVec3 &_v)
{
	p = _p;
	v = _v;
	v.Normalize();
}

/*!
*	\brief 3���� �������� �� ���� ������ ������ �����ϴ� ������.
*	
*	\param _p �������� ��
*	\param _q �������� ��
*/
GLine::GLine(const GPos3 &_p, const GPos3 &_q)
{
	p = _p;
	v = _q - _p;
	v.Normalize();
}

/*!
*	\brief ���������.
*	
*	\param copy ����� ������ ��ü.
*/
GLine::GLine(const GLine &copy)
: p(copy.p), v(copy.v)
{
}

/*!
*	\brief �Ҹ���.
*/
GLine::~GLine()
{
}

/*!
*	\brief	���Կ����� �ߺ�
*	
*	\param rhs ������ �ǿ�����.
*
*	\return ���Ե� �ڽ��� ��ȯ�Ѵ�.
*/
GLine &GLine::operator =(const GLine &rhs)
{
	this->p = rhs.p;
	this->v = rhs.v;
	return *this;
}

/*!
*	\brief	�Լ�ȣ�⿬���� �ߺ�
*			- �������� �Ű����� t������ �� l(t)�� ���Ѵ�.
*	
*	\param t �Ű�����.
*
*	\return �������� �� l(t)�� ��ȯ�Ѵ�.
*/
GPos3 GLine::Eval(const double t) const
{
	return p + t * v;
}

/*!
*	\brief	��ȣ�Կ����� �ߺ�.
*	
*	\param rhs ������ �ǿ�����.
*
*	\return true: ������, false: �ٸ���.
*/
bool operator ==(const GLine &lhs, const GLine &rhs)
{
	if (lhs.IsOnLine(rhs.p) && EQ_ZERO(norm(lhs.v ^ rhs.v), GLine::Precision))
		return true;
	else
		return false;
}

/*!
*	\brief	�ε�ȣ�Կ����� �ߺ�.
*	
*	\param rhs ������ �ǿ�����.
*
*	\return true: �ٸ���, false: ������.
*/
bool operator !=(const GLine &lhs, const GLine &rhs)
{
	return !(lhs == rhs);
}

/*!
*	\brief �� q�� �������� ������ �����Ѵ�.
*	
*	\param q ������ ��.
*
*	\return true: q�� �������� �� �ϰ��, false: �ƴҰ��.
*/
bool GLine::IsOnLine(const GPos3 &q) const
{
	GVec3 w = q - p;
	double s = norm(v ^ w);
	if (EQ_ZERO(s, Precision))
		return true;
	else
		return false;
}

/*!
*	\brief ��¿����� �ߺ�.
*
*	\param os ��½�Ʈ��
*	\param l ����� ���ΰ�ü
*
*	\return ��µ� ��Ʈ��
*/
std::ostream &operator <<(std::ostream &os, const GLine &l)
{
	os << "(" 
		<< l.p[0] << " + (" << l.v[0] << ") * t, "
		<< l.p[1] << " + (" << l.v[1] << ") * t, "
		<< l.p[2] << " + (" << l.v[2] << ") * t)";
	return os;
}

/*!
*	\brief �� ������ ���������� �Ÿ��� ���Ѵ�.
*
*	\param l ����
*	\param q �� ��
*
*	\return �� \a q���� ���� \a l������ �����Ÿ�
*/
double dist(const GLine &l, const GPos3 &q)
{
	return norm(proj(q - l.p, l.v) - (q - l.p));
}

/*!
*	\brief �� ���� l1(t)�� l2(t)������ �ִ� �Ÿ��� ���Ѵ�.
*
*	\param l1 ù ��° ����
*	\param l2 �� ��° ����
*	\param t1 �ִ� �Ÿ��� ����� l1�� �ĸ����� ���� �����
*	\param t2 �ִ� �Ÿ��� ����� l2�� �ĸ����� ���� �����
*
*	\return �� ���� ������ �ִܰŸ��� ����Ͽ� ��ȯ�Ѵ� (�� ������ ������ ��� -1.0�� ��ȯ�Ѵ�).
*/
double dist(const GLine &l1, const GLine &l2, double &t1, double &t2)
{
	GPos3 p1 = l1.p;
	GPos3 p2 = l2.p;
	GVec3 v1 = l1.v;
	GVec3 v2 = l2.v;

	double a11 = v1 * v1;
	double a12 = -v2 * v1;
	double a21 = v1 * v2;
	double a22 = -v2 * v2;
	double b1 = (p1 - p2) * v1;
	double b2 = (p1 - p2) * v2;
	double D = a11 * a22 - a12 * a21;

	double ret = 0.0;
	if (EQ_ZERO(D, 0.00001))
	{
		t1 = 0.0;
		t2 = 0.0;
		ret = -1.0;
	}
	else
	{
		t1 = (a22 * b1 - a12 * b2) / D;
		t2 = (-a21 * b1 + a11 * b2) / D;

		GPos3 q1 = l1.Eval(t1);
		GPos3 q2 = l2.Eval(t2);

		ret = dist(q1, q2);
	}

	return ret;
}

/*!
*	\brief ���ο� ���� �������� ������ �������� �����Ѵ� (������ �������).
*
*	\param _p ���ο� ��
*
*	\return ����� �ڽ��� ��ȯ�Ѵ�.
*/
GLine &GLine::SetPt(const GPos3 &_p)
{
	p = _p;
	return *this;
}

/*!
*	\brief ������ ������ �����Ѵ�.
*
*	\param _v ���ο� ����.
*
*	\return ����� �ڽ��� ��ȯ�Ѵ�.
*/
GLine &GLine::SetDir(const GVec3 &_v)
{
	v = _v;
	return *this;
}

/*!
*	\brief ������ �������� �����Ѵ�.
*
*	\return ������ ������.
*/
GPos3 GLine::GetPt() const
{
	return p;
}

/*!
*	\brief ������ ������ �����Ѵ�.
*
*	\return ������ ����.
*/
GVec3 GLine::GetDir() const
{
	return v;
}

/*!
*	\brief ��ġ������ �Ѱ�ġ�� �����Ѵ�.
*/
void GLine::SetPrecision(double err)
{
	Precision = err;
}

/*!
*	\brief ��ġ������ �Ѱ�ġ�� �����Ѵ�.
*
*	\return �Ѱ�ġ.
*/
double GLine::GetPrecision()
{
	return Precision;
}

///////////////////////////////////////////////////////////

/*!
*	\brief ����� ������.
*	
*	\param _n �����Ǵ� ����� ��������
*	\param _p �����Ǵ� ������� ������ ����
*/
GPlane::GPlane(const GVec3 &_n, const GPos3 &_p)
{
	n = _n;
	d = -(n[0] * _p[0] + n[1] * _p[1] + n[2] * _p[2]);
}

/*!
*	\brief �� �� p1, p2, p3 �� ������ ����� ������
*	
*	\param p1 ������ ��.
*	\param p2 ������ ��.
*	\param p3 ������ ��.
*/
GPlane::GPlane(const GPos3 &p1, const GPos3 &p2, const GPos3 &p3)
{
	n = (p2 - p1) ^ (p3 - p1);
	d = -(n[0] * p1[0] + n[1] * p1[1] + n[2] * p1[2]);
}

/*!
*	\brief ����� ���������
*	
*	\param copy ����� ����� ��ü�� ���� ���۷���
*/
GPlane::GPlane(const GPlane &cpy)
: n(cpy.n), d(cpy.d)
{
}

/*!
*	\brief ����� ������.
*	
*	\param _n ��������.
*	\param _d ��� d = - n * p (p: ������� ������ ��).
*/
GPlane::GPlane(const GVec3 &_n, const double &_d)
: n(_n), d(_d)
{
}

/*!
*	\brief ����� ������.
*	
*	\param a, b, c, d ��� ������ ax + by + cz +d = 0 �� ���
*/
GPlane::GPlane(const double &a, const double &b, const double &c, const double &d)
{
	this->n = GVec3(a, b, c);
	this->d = d;
}

/*!
*	\brief ����� �Ҹ���.
*/
GPlane::~GPlane()
{
}

/*!
*	\brief ���Կ����� �ߺ�
*	
*	\param rhs ������ �ǿ�����
*
*	\return ���Ե� �ڽ��� ��ȯ�Ѵ�.
*/
GPlane &GPlane::operator =(const GPlane &rhs)
{
	this->n = rhs.n;
	this->d = rhs.d;
	return *this;
}

/*!
*	\brief �������͸� ��ȯ�Ѵ�.
*
*	\return ��������.
*/
GVec3 GPlane::GetNormal() const
{
	return n;
}

/*!
*	\brief �� p�� ������ �� ������ ����.
*	
*	\param p ������ ��
*
*	\return true: �� p�� ������ �� �ϰ��, false: �׷��� �������.
*/
bool GPlane::IsOnPlane(const GPos3 &p) const
{
	double s;
	s = -(n[0] * p[0] + n[1] * p[1] + n[2] * p[2]);
	if (EQ(s, d, GPlane::Precision))
		return true;
	else
		return false;
}

/*!
*	\brief �� p�� ����� ���� �������� ����.
*	
*	\param p ������ ��
*
*	\return true: �� p�� ����� ���� �� �ϰ��, false: �׷��� �������.
*/
bool GPlane::IsAbovePlane(const GPos3 &p) const
{
	double s;
	s = n[0] * p[0] + n[1] * p[1] + n[2] * p[2] + d;
	if (s > 0.0)
		return true;
	else
		return false;
}

/*!
*	\brief �� p�� ����� �Ʒ��� �������� ����.
*	
*	\param p ������ ��
*
*	\return true: �� p�� ����� �Ʒ��� �� �ϰ��, false: �׷��� �������.
*/
bool GPlane::IsBelowPlane(const GPos3 &p) const
{
	double s;
	s = n[0] * p[0] + n[1] * p[1] + n[2] * p[2] + d;
	if (s < 0.0)
		return true;
	else
		return false;
}

/*!
*	\brief ��ġ������ �Ѱ�ġ�� �����Ѵ�.
*/
void GPlane::SetPrecision(const double err)
{
	Precision = err;
}

/*!
*	\brief ��ġ������ �Ѱ�ġ�� �����Ѵ�.
*
*	\return �Ѱ�ġ.
*/
double GPlane::GetPrecision()
{
	return Precision;
}

/*!
*	\brief ��¿����� �ߺ�.
*
*	\param os ��½�Ʈ��.
*	\param pi ����� ��鰴ü.
*
*	\return ��½�Ʈ��
*/
std::ostream &operator <<(std::ostream &os, const GPlane &pi)
{
	os << "(" << pi.n[0] << ") * x + (" 
		<< pi.n[1] << ") * y + ("
        << pi.n[2] << ") * z + ("
		<< pi.d << ") = 0";
	return os;
}

/*!
*	\brief	��� pi���� �� p������ ��ȣ�ִ� �Ÿ��� ����Ѵ�.
*
*	\param pi ����� ��ü.
*	\param p ��� ���� ����.
*
*	\return ��� \a pi���� �� \a p������ ��ȣ�ִ� �Ÿ�
*/
double dist(const GPlane &pi, const GPos3 &p)
{
    double D;
	D = (p[0] * pi.n[0] + p[1] * pi.n[1] + p[2] * pi.n[2] + pi.d) / norm(pi.n);
	return D;
}

/*!
*	\brief	�� p�� ��� pi�� �翵��Ų ���� ���Ѵ�.
*
*	\param p ��� ���� ��.
*	\param pi ��鰴ü.
*/
GPos3 proj(const GPos3 &p, const GPlane &pi)
{
	double s = -dist(pi, p) / norm(pi.n);
	return p + s * pi.n;
}

/*!
*	\brief	������ ������ �������� ����Ѵ�.
*
*	\param p �������� ����� ����
*	\param l0 ù��° ������ ������ (ruling line)
*	\param l1 �ι�° ������ ������ (boundary line)
*	\param t0 ù��° ������ �������� �Ķ���� ���� �����
*	\param t1 �ι�° ������ �������� �Ķ���� ���� �����
*
*	\return true: ����, false: ������ ���� ��ġ�� �ְų�, (0 ~ 1)���̸� ��� ���
*/
bool intersect_line_line(GPos3 &p, const GLine &l0, const GLine &l1, double &t0, double &t1)
{
	double a = l0.v[0];
	double b = -l1.v[0];
	double c = l0.v[1];
	double d = -l1.v[1];
	double e = l1.p[0] - l0.p[0];
	double f = l1.p[1] - l0.p[1];

	double det = a * d - b * c;
	if (EQ(det, 0.0, 1.0e-6))
		return false;

	t0 = (d * e - b * f) / det;
	t1 = (a * f - c * e) / det;

	if (EQ(t0, 0.0, 1.0e-6))
		t0 = 0.0;

	if (EQ(t0, 1.0, 1.0e-6))
		t0 = 1.0;

	if (EQ(t1, 0.0, 1.0e-6))
		t1 = 0.0;

	if (EQ(t1, 1.0, 1.0e-6))
		t1 = 1.0;

	if (t0 < 0.0 || t0 > 1.0)
		return false;

	if (t1 < 0.0 || t1 > 1.0)
		return false;

	// p = l0.Eval(t0);
	p = l1.Eval(t1);

	return true;
}

/*!
*	\brief	������ ������ �������� ����Ѵ�.
*
*	\param p �������� ����� ����
*	\param l0 ù��° ������ ������ (ruling line)
*	\param l1 �ι�° ������ ������ (boundary line)
*
*	\return true: ����, false: ������ ���� ��ġ�� �ִ� ���
*/
bool intersect_line_line2(GPos3 &p, GLine &l0, GLine &l1)
{
	double a = l0.v[0];
	double b = -l1.v[0];
	double c = l0.v[1];
	double d = -l1.v[1];
	double e = l1.p[0] - l0.p[0];
	double f = l1.p[1] - l0.p[1];

	double det = a * d - b * c;
	if (EQ(det, 0.0, 0.00001))
		return false;

	double t0, t1;
	t0 = (d * e - b * f) / det;
	t1 = (a * f - c * e) / det;

	// p = l0.Eval(t0);
	p = l1.Eval(t1);

	return true;
}

/*!
*	\brief	������ ����� �������� ����Ѵ�.
*
*	\param p �������� ����� ����.
*	\param l ���� ��ü.
*	\param pi ��� ��ü.
*
*	\return true: ����, false: ������ ���� �����ϰų�, ����� ������ �����ϴ� ���.
*/
bool intersect_line_plane(GPos3 &p, const GLine &l, const GPlane &pi)
{
	if (EQ_ZERO(l.v * pi.n, GPlane::Precision))
	{
		std::cout << "line is parallel to plane !" << std::endl;
		return false;
	}

	double t = -(l.p[0] * pi.n[0] + l.p[1] * pi.n[1] + l.p[2] * pi.n[2] + pi.d) / (l.v * pi.n);
	p = l.Eval(t);
    return true;
}

/*!
*	\brief	������ �ﰢ�� (p1p2p3)�� �������� ����Ѵ�.
*
*	\param p1 �ﰢ���� ����
*	\param p2 �ﰢ���� ����
*	\param p3 �ﰢ���� ����
*	\param l ������ ������
*	\param t q = l(t)�� �����ϴ� ������ �Ķ����
*	\param q �������� �����
*	\param alpha barycentric ��ǥ�� �����
*	\param beta barycentric ��ǥ�� �����
*	\param gamma barycentric ��ǥ�� �����
*	\param bCullBackFace ������ �ﰢ���� �޸�� ������ ��츦 �����Ϸ���. (����Ʈ: true).
*	\note q = alpha * p1 + beta * p2 + gamma * p3, (alpha + beta + gamma = 1)
*
*	\return true: ����, false: ������ �ﰢ���� �����ϰų� �������� �ﰢ���� �ܺο� �����ϴ� ���.
*/
bool intersect_line_triangle(const GPos3 &p1, const GPos3 &p2, const GPos3 &p3, const GLine &l, double &t, GPos3 &q, double &alpha, double &beta, double &gamma, const bool bCullBackFace)
{
	GVec3 e1, e2, u, v, w;
	double det;
	e1 = p1 - p3;
	e2 = p2 - p3;
	u = l.v ^ e2;
	det = e1 * u;

	if (bCullBackFace)	// ������ �ﰢ���� �޸�� ������ ���� ����.
	{
		if (det < GLine::Precision)
			return false;

		w = l.p - p3;
		alpha = w * u;
		if (alpha < 0.0 || alpha > det)
			return false;

		v = w ^ e1;
		beta = l.v * v;
		if (beta < 0.0 || alpha + beta > det)
			return false;

		t = e2 * v;

		alpha /= det;
		beta /= det;
		t /= det;
	}
	else
	{
		if (det > -GLine::Precision && det < GLine::Precision)
			return false;

		w = l.p - p3;
		alpha = w * u / det;
		if (alpha < 0.0 || alpha > 1.0)
			return false;

		v = w ^ e1;
		beta = l.v * v / det;
		if (beta < 0.0 || alpha + beta > 1.0)
			return false;

		t = e2 * v / det;
	}

	gamma = 1.0 - alpha - beta;
	q = l.Eval(t);
	return true;
}

//////////////////////////////////////////////////////////////
GSphere::GSphere(GPos3 _Pos, double _Rad)
{
	Pos = _Pos;
	Rad = _Rad;
}


GSphere::GSphere(const GSphere &cpy)
{
	Pos = cpy.Pos;
	Rad = cpy.Rad;
	Ka = cpy.Ka;
	Kd = cpy.Kd;
	Ks = cpy.Ks;
	ns = cpy.ns;
}

GSphere::~GSphere()
{
}

GSphere &GSphere::operator =(const GSphere &rhs)
{
	Pos = rhs.Pos;
	Rad = rhs.Rad;
	Ka = rhs.Ka;
	Kd = rhs.Kd;
	Ks = rhs.Ks;
	ns = rhs.ns;
	
	return *this;
}

//////////////////////////////////////////////////////////////
GLight::GLight(GPos3 _Pos, GVec3 _Ia, GVec3 _Id, GVec3 _Is)
{
	Pos = _Pos;
	Ia = _Ia;
	Id = _Id;
	Is = _Is;
}

GLight::GLight(const GLight &cpy)
{
	Pos = cpy.Pos;
	Ia = cpy.Ia;
	Id = cpy.Id;
	Is = cpy.Is;
}

GLight::~GLight()
{
}

GLight &GLight::operator = (const GLight &rhs)
{
	Pos = rhs.Pos;
	Ia = rhs.Ia;
	Id = rhs.Id;
	Is = rhs.Id;

	return *this;
}
