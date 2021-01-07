#ifndef _GMATH_H
#define _GMATH_H

#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdarg>
#include <iomanip>
#include <vector>

// ��ũ�� ���
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616

// ��ũ�� ����
#define SQRT(X)		sqrt((X))
#define SQR(X)		((X) * (X))
#define DEG2RAD(X)	((X) * (M_PI) / (180.0))
#define RAD2DEG(X)	((X) * (180.0) / (M_PI))
#define SWAP(type, x, y) { type temp = (x); (x) = (y); (y) = temp; }
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define ABS(X)		(((X) > 0.0) ? (X) : (-(X)))
#define SIGN(a)		((a) > 0.0 ? (1.0) : (-1.0))
#define SIGN1(a, b) ((b) > 0.0 ? ABS(a) : -ABS(a))
#define SIGN2(a, b)	((b) >= 0.0 ? fabs(a) : -fabs(a))
#define PYTHAG(a, b) SQRT((SQR(a) + SQR(b)))
#define EQ(X, Y, EPS)	(ABS((X) - (Y)) < EPS)
#define EQ_ZERO(X, EPS) (ABS(X) < EPS)
#define ARR_ZERO(A, N) memset((A), 0, sizeof(A[0]) * (N))
#define ARR_COPY(D, S, N) memmove((D), (S), sizeof(S[0]) * (N))
#define ARR_COPY_2D(D, S, M, N) \
	for (int i = 0; i < (M); ARR_COPY(D[i], S[i], N), ++i);
#define ARR_ALLOC(D, TYPE, N) D = new TYPE [(N)]
#define ARR_ALLOC_2D(D, TYPE, M, N) \
	D = new TYPE *[(M)]; \
	for (int i = 0; i < (M); D[i] = new TYPE [(N)], ++i);
#define ARR_FREE(D) \
	delete [] D; \
	D = NULL
#define ARR_FREE_2D(D, M) \
	for (int i = 0; i < (M); delete [] D[i], ++i); \
	delete [] D; \
	D = NULL
#define MTYPE_EPS	1.0e-15

// Ŭ���� ����.
class GVec3;
class GPos3;
class GLine;
class GPlane;

/*!
*	\class GVec3
*	\brief 3���� ���͸� ǥ���ϴ� Ŭ����
*
*	\author ������(shyun@dongguk.edu)
*	\date 01 Jan 2001	
*/
class GVec3
{
	// ������ �Լ� �� Ŭ����
	friend GVec3 operator +(const GVec3 &lhs, const GVec3 &rhs);
	friend GPos3 operator +(const GVec3 &lhs, const GPos3 &rhs);
	friend GVec3 operator -(const GVec3 &lhs, const GVec3 &rhs);
	friend GVec3 operator *(const GVec3 &lhs, const double &s);
	friend GVec3 operator *(const double &s, const GVec3 &rhs);
	friend double operator *(const GVec3 &lhs, const GVec3 &rhs);
	friend GVec3 operator /(const GVec3 &lhs, const double &s);
	friend GVec3 operator ^(const GVec3 &lhs, const GVec3 &rhs);
	friend bool operator ==(const GVec3 &lhs, const GVec3 &rhs);
	friend bool operator !=(const GVec3 &lhs, const GVec3 &rhs);
	friend std::ostream &operator <<(std::ostream &os, const GVec3 &v);
	friend std::istream &operator >>(std::istream &is, GVec3 &v);
	friend GVec3 proj(const GVec3 &v, const GVec3 &w);
	friend GVec3 ortho(const GVec3 &v);
	friend double dist(const GVec3 &v, const GVec3 &w);
	friend double det(const GVec3 &u, const GVec3 &v, const GVec3 &w);
	friend double norm(const GVec3 &v);
	friend double angle(const GVec3 &v, const GVec3 &w, bool radian = false);
	friend double angle(const GVec3 &v, const GVec3 &w, const GVec3 &up, bool radian = false);
	friend GPos3 cast_pt3(const GVec3 &v);
	
public:
	// ������ �� �Ҹ���
	GVec3(double x = 0.0, double y = 0.0, double z = 0.0);
	GVec3(const GVec3 &cpy);
	~GVec3();

	// ���� �� ���մ��Կ�����
	GVec3 &operator =(const GVec3 &rhs);
	GVec3 &operator +=(const GVec3 &rhs);
	GVec3 &operator -=(const GVec3 &rhs);
	GVec3 &operator *=(const double &s);
	GVec3 &operator /=(const double &s);
	GVec3 &operator ^=(const GVec3 &rhs);

	// ���׿�����
	GVec3 operator +() const;
	GVec3 operator -() const;

	// ÷�ڿ�����
	double &operator [](const int &idx);
	const double &operator [](const int &idx) const;

	// ����Լ�
	GVec3 &Set(const double &x, const double &y, const double &z);
	GVec3 &Normalize();
		
	// �����ɹ��Լ�
	static void SetPrecision(double error);
	static double GetPrecision();

public:
	// ������ ���
	/*! \brief 3���� ������ ���Ҹ� �����ϴ� �Ǽ� �迭 */
	double V[3];

	/*! \brief ��ȣ �� �ε�ȣ�������� �����Ѱ� */
	static double Precision;
};

/*!
*	\class GPos3
*	\brief 3���� ������ ��ġ�� ��Ÿ���� Ŭ����
*
*	\author ������(shyun@dongguk.edu)
*	\date 01 Jan 2001	
*/
class GPos3
{
	// ������ �Լ� �� Ŭ����
	friend GVec3 operator -(const GPos3 &lhs, const GPos3 &rhs);
	friend GPos3 operator -(const GPos3 &lhs, const GVec3 &rhs);
	friend GPos3 operator +(const GPos3 &lhs, const GVec3 &rhs);
	friend GPos3 operator +(const GVec3 &lhs, const GPos3 &rhs);
	friend bool operator ==(const GPos3 &lhs, const GPos3 &rhs);
	friend bool operator !=(const GPos3 &lhs, const GPos3 &rhs);
	friend std::ostream &operator <<(std::ostream &os, const GPos3 &p);
	friend std::istream &operator >>(std::istream &is, GPos3 &p);
	friend double norm(const GPos3 &p);
	friend double dist(const GPos3 &p, const GPos3 &q);
	friend double dist_sq(const GPos3 &p, const GPos3 &q);
	friend GPos3 affine_sum(int N, ...);
	friend GPos3 affine_sum(GPos3 *Points, double *Weights, const int Size);
	friend GVec3 cast_GVec3(const GPos3 &p);
	friend GPos3 round_off(const GPos3 &p, int place);
	
public:
	// ������ �� �Ҹ���
	GPos3(double x = 0.0, double y = 0.0, double z = 0.0);
	GPos3(const GPos3 &cpy);
	~GPos3();

	// ���Կ�����
	GPos3 &operator =(const GPos3 &rhs);
	GPos3 &operator +=(const GVec3 &rhs);

	// ÷�ڿ�����
	double &operator [](const int &idx);
	const double &operator [](const int &idx) const;

	// ����Լ�
	GPos3 &Set(const double &x, const double &y, const double &z);
	
	// �����Լ�
	static void SetPrecision(double error);
	static double GetPrecision();
   
public:
	/*! \brief 3���� ������ ���Ҹ� �����ϴ� �Ǽ��迭 */	
	double V[3];	
	/*! \brief ��ȣ �� �ε�ȣ�������� �����Ѱ� */
	static double Precision;	
};

/*!
*	\class GLine
*	\brief 3���� ������ ������ ��Ÿ���� Ŭ����
*
*	\author ������(shyun@dongguk.edu)
*	\date 01 Jan 2001	
*/
class GLine
{
	// ������ �Լ� �� Ŭ����
	friend bool operator ==(const GLine &lhs, const GLine &rhs);
	friend bool operator !=(const GLine &lhs, const GLine &rhs);
	friend std::ostream &operator <<(std::ostream &os, const GLine &l);
	friend double dist(const GLine &l, const GPos3 &q);
	friend double dist(const GLine &l0, const GLine &l1, double &t1, double &t2);
	friend bool intersect_line_line(GPos3 &p, const GLine &l0, const GLine &l1, double &t0, double &t1);
	friend bool intersect_line_line2(GPos3 &p, GLine &l0, GLine &l1);
	friend bool intersect_line_plane(GPos3 &p, const GLine &l, const GPlane &pi);
	friend bool intersect_line_triangle(const GPos3 &p1, const GPos3 &p2, const GPos3 &p3, const GLine &l, double &t, GPos3 &q, double &alpha, double &beta, double &gamma, const bool bCull = true);
	friend bool intersect_planes(GLine &l, const GPlane &pi1, const GPlane &pi2);
	
public:
	// ������ �� �Ҹ���
	GLine(const GPos3 &_p = GPos3(0, 0, 0), const GVec3 &_v = GVec3(0, 0, 0));
	GLine(const GPos3 &_p, const GPos3 &_q);
	GLine(const GLine &cpy);
	~GLine();

	// ���Կ�����
	GLine &operator =(const GLine &rhs);
	
	// ����Լ�
	GLine &SetPt(const GPos3 &_p);
	GLine &SetDir(const GVec3 &_v);
	GPos3 GetPt() const;
	GVec3 GetDir() const;
	bool IsOnLine(const GPos3 &q) const;
	GPos3 Eval(const double t) const;

	// ��������Լ�
	static void SetPrecision(double err);
	static double GetPrecision();

public:
	// ������ ���.
	/*! \brief �������� �� �� */
	GPos3 p;
	/*! \brief ������ ���� ���� l(t) = p + v * t */
	GVec3 v;
	/*! \brief ��ȣ �� �ε�ȣ�������� �����Ѱ� */
	static double Precision;
};

/*!
*	\class GPlane
*	\brief ����� ǥ���ϴ� Ŭ����
*
*	\author ������(shyun@dongguk.edu)
*	\date 01 Jan 2001	
*/
class GPlane
{
	// ������ �Լ� �� Ŭ����
	friend std::ostream &operator <<(std::ostream &os, const GPlane &pi);
	friend double dist(const GPlane &pi, const GPos3 &p);
	friend GPos3 proj(const GPos3 &p, const GPlane &pi);
	friend bool intersect_line_plane(GPos3 &p, const GLine &l, const GPlane &pi);
	
public:
	// ������ �� �Ҹ���
	GPlane(const GVec3 &_n, const GPos3 &_p);
	GPlane(const GPos3 &p1, const GPos3 &p2, const GPos3 &p3);
	GPlane(const GVec3 &_n, const double &_d);
	GPlane(const double &a, const double &b, const double &c, const double &d);
	GPlane(const GPlane &cpy);
	~GPlane();

	// ���Կ�����
	GPlane &operator =(const GPlane &rhs);
	
	// ����Լ�
	GVec3 GetNormal() const;
    bool IsOnPlane(const GPos3 &p) const;
	bool IsAbovePlane(const GPos3 &p) const;
	bool IsBelowPlane(const GPos3 &p) const;

	// �����Լ�
	static void SetPrecision(const double err);
	static double GetPrecision();
    
public:
	// ������ ���
	/*! \brief ����� ������(ax + by + cz + d = 0)���� ���� ���� n=(a, b, c) */
	GVec3 n;
	/*! \brief ����� ������(ax + by + cz + d = 0)���� ��� d(= -n * p) */
	double d;
	/*! \brief ��ȣ �� �ε�ȣ�������� �����Ѱ� */
	static double Precision;
};

/*!
*	\class GSphere
*	\brief 3���� ���� ǥ���ϴ� Ŭ����
*
*	\author ������(shyun@dongguk.edu)
*	\date 18 Sept. 2016	
*/
class GSphere
{
public:
	// ������ �� �Ҹ���
	GSphere(GPos3 _Pos = GPos3(0.0, 0.0, 0.0), double _Rad = 0.0);
	GSphere(const GSphere &cpy);
	~GSphere();

	// ���� ������ 
	GSphere &operator =(const GSphere &rhs);

public:
	// ������ ���
	GPos3 Pos;		// ���� �߽��� ��ġ
	double Rad;		// ���� ������
	GVec3 Ka;		// �ֺ��� �ݻ���
	GVec3 Kd;		// ���ݻ� ���
	GVec3 Ks;		// ���ݻ� ���	
	double ns;		// ���ݻ� ����
};

/*!
*	\class GLight
*	\brief 3���� ������ ������ ǥ���ϴ� Ŭ����
*
*	\author ������(shyun@dongguk.edu)
*	\date 18 Sept. 2016	
*/
class GLight
{
public:
	// ������ �� �Ҹ���
	GLight(GPos3 _Pos = GPos3(), GVec3 _Ia = GVec3() , GVec3 _Id = GVec3() , GVec3 _Is = GVec3());
	GLight(const GLight &cpy);
	~GLight();

	// ���� ������
	GLight &operator = (const GLight &rhs);

public:
	// ������ ���
	GPos3 Pos;		// ������ ��ġ
	GVec3 Ia;		// �ֺ��� ����
	GVec3 Id;		// ���ݻ籤 ����
	GVec3 Is;		// ���ݻ籤 ����
};

#endif // _GMATH_H

