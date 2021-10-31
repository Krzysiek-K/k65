
#ifndef _BASE_MATH_H
#define _BASE_MATH_H


#include <math.h>
#include <stdint.h>

// TODO: remove this dependency
//#include <d3d9.h>
//#include <d3dx9.h>


//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")


#ifndef M_PI
#define M_PI	3.14159265
#endif


#define _INLINE	inline


namespace base {


template<class T>
struct vector3d {
	typedef vector3d<T> V;

	T x,y,z;


	_INLINE vector3d() {}
	_INLINE vector3d(T _x,T _y,T _z) : x(_x), y(_y), z(_z) {}

#if 1
    friend _INLINE V operator -(const V &a) { return V(-a.x,-a.y,-a.z); }
	friend _INLINE V operator +(const V &a,const V &b) { return V(a.x+b.x,a.y+b.y,a.z+b.z); }
	friend _INLINE V operator +(const V &a,T b) { return V(a.x+b,a.y+b,a.z+b); }
	friend _INLINE V operator -(const V &a,const V &b) { return V(a.x-b.x,a.y-b.y,a.z-b.z); }
	friend _INLINE V operator -(const V &a,T b) { return V(a.x-b,a.y-b,a.z-b); }
	friend _INLINE V operator *(const V &a,T s) { return V(a.x*s,a.y*s,a.z*s); }
	friend _INLINE V operator *(T s,const V &a) { return V(a.x*s,a.y*s,a.z*s); }
	friend _INLINE V operator /(const V &a,T s) { return (s!=0)?V(a.x/s,a.y/s,a.z/s):V(0,0,0); }
	friend _INLINE V operator /(const V &a,const V &b) { return V(b.x?a.x/b.x:0,b.y?a.y/b.y:0,b.z?a.z/b.z:0); }
	friend _INLINE const V &operator +=(V &a,const V &b) { a.x+=b.x; a.y+=b.y; a.z+=b.z; return a; }
	friend _INLINE const V &operator +=(V &a,T b) { a.x+=b; a.y+=b; a.z+=b; return a; }
	friend _INLINE const V &operator -=(V &a,const V &b) { a.x-=b.x; a.y-=b.y; a.z-=b.z; return a; }
	friend _INLINE const V &operator -=(V &a,T b) { a.x-=b; a.y-=b; a.z-=b; return a; }
	friend _INLINE const V &operator *=(V &a,const V &b) { a.x*=b.x; a.y*=b.y; a.z*=b.z; return a; }
	friend _INLINE const V &operator *=(V &a,T s) { a.x*=s; a.y*=s; a.z*=s; return a; }
	friend _INLINE const V &operator /=(V &a,T s) { if(s!=0) { a.x/=s; a.y/=s; a.z/=s; } else { a.x=0; a.y=0; a.z=0; } return a; }
	friend _INLINE const V &operator /=(V &a,const V &b) { a.x=b.x?a.x/b.x:0; a.y=b.y?a.y/b.y:0; a.z=b.z?a.z/b.z:0; }
	friend _INLINE bool operator ==(const V &a,const V &b) { return (a.x==b.x)&&(a.y==b.y)&&(a.z==b.z); }
#else
	_INLINE _V operator -() const { return _V(-x,-y,-z); }
	_INLINE _V operator +(const _V &v) const { return _V(x+v.x,y+v.y,z+v.z); }
	_INLINE _V operator -(const _V &v) const { return _V(x-v.x,y-v.y,z-v.z); }
	_INLINE _V operator *(_T s) const { return _V(x*s,y*s,z*s); }
	_INLINE _V operator /(_T s) const { return (s!=0)?_V(x/s,y/s,z/s):_V(0,0,0); }
	_INLINE _V &operator +=(const _V &v) { x+=v.x; y+=v.y; z+=v.z; return *this; }
	_INLINE _V &operator -=(const _V &v) { x-=v.x; y-=v.y; z-=v.z; return *this; }
	_INLINE _V &operator *=(_T s) { x*=s; y*=s; z*=s; return *this; }
	_INLINE _V &operator /=(_T s) { if(s!=0) { x/=s; y/=s; z/=s; } else { x=0; y=0; z=0; } return *this; }
	_INLINE bool operator ==(const _V &v) const { return (x==v.x)&&(y==v.y)&&(z==v.z); }
#endif

	_INLINE bool all_lequal(const V &v) const { return (x<=v.x)&&(y<=v.y)&&(z<=v.z); }
	_INLINE bool all_gequal(const V &v) const { return (x>=v.x)&&(y>=v.y)&&(z>=v.z); }

	_INLINE T length()		const { return sqrt(dot(*this)); }
	_INLINE T length2()	const { return dot(*this); }

	_INLINE void normalize()
	{
		T len = length();
		if(!len) return;
		x/=len; y/=len; z/=len;
	}

	_INLINE V get_normalized() const
	{
		V v = *this;
		v.normalize();
		return v;
	}

	_INLINE T dot(const V &v) const { return x*v.x + y*v.y + z*v.z; }
	_INLINE V cross(const V &v) const { return V(y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x); }
	
	_INLINE void set_mins(const V &v)
	{
		if(v.x<x) x=v.x;
		if(v.y<y) y=v.y;
		if(v.z<z) z=v.z;
	}

	_INLINE void set_maxs(const V &v)
	{
		if(v.x>x) x=v.x;
		if(v.y>y) y=v.y;
		if(v.z>z) z=v.z;
	}

	_INLINE V transform3x3(const T *mtx)
	{
		return V(x*mtx[0]+y*mtx[1]+z*mtx[2],x*mtx[3]+y*mtx[4]+z*mtx[5],x*mtx[6]+y*mtx[7]+z*mtx[8]);
	}

	_INLINE void scale_xyz(const V &v) { x*=v.x; y*=v.y; z*=v.z; }
	_INLINE V get_scaled_xyz(const V &v) const { return V(x*v.x,y*v.y,z*v.z); }

	_INLINE void update_min_max(V &min,V &max) const
	{
		if(x<min.x) min.x=x;
		if(y<min.y) min.y=y;
		if(z<min.z) min.z=z;
		if(x>max.x) max.x=x;
		if(y>max.y) max.y=y;
		if(z>max.z) max.z=z;
	}

	_INLINE void saturate()
	{
		if(x<0) x = 0;
		if(x>1) x = 1;
		if(y<0) y = 0;
		if(y>1) y = 1;
		if(z<0) z = 0;
		if(z>1) z = 1;
	}

	_INLINE uint32_t make_rgb() const			{ return (int(x*255)<<16) | (int(y*255)<<8) | int(z*255); }
	_INLINE uint32_t make_rgba(float a) const	{ return (int(a*255)<<24) | (int(x*255)<<16) | (int(y*255)<<8) | int(z*255); }

//	_INLINE D3DXVECTOR3 &d3dx() { return *(D3DXVECTOR3*)this; }
//	_INLINE const D3DXVECTOR3 &d3dx() const { return *(const D3DXVECTOR3*)this; }

	_INLINE void unpack_rgb(uint32_t rgb)
	{
		x = ((rgb>>16)&0xFF)*(1/255.0f);
		y = ((rgb>> 8)&0xFF)*(1/255.0f);
		z = ((rgb    )&0xFF)*(1/255.0f);
	}

	_INLINE float unpack_rgba(uint32_t rgba)
	{
		unpack_rgb(rgba);
		return ((rgba>>24)&0xFF)*(1/255.0f);
	}

	static _INLINE V from_rgb(uint32_t rgb)
	{
		return V(	((rgb>>16)&0xFF)*(1/255.0f),
					((rgb>> 8)&0xFF)*(1/255.0f),
					((rgb    )&0xFF)*(1/255.0f) );
	}
};

typedef vector3d<float> vec3;
typedef vector3d<int> ivec3;


template<class T>
struct vector2d {
	typedef vector2d<T> V;

	T x,y;
	

	_INLINE vector2d() {}
	_INLINE vector2d(T _x,T _y) : x(_x), y(_y) {}

#if 1
    friend _INLINE V operator -(const V &a) { return V(-a.x,-a.y); }
	friend _INLINE V operator +(const V &a,const V &b) { return V(a.x+b.x,a.y+b.y); }
	friend _INLINE V operator +(const V &a,T b) { return V(a.x+b,a.y+b); }
	friend _INLINE V operator +(T a,const V &b) { return V(a+b.x,a+b.y); }
	friend _INLINE V operator -(const V &a,const V &b) { return V(a.x-b.x,a.y-b.y); }
	friend _INLINE V operator -(const V &a,T b) { return V(a.x-b,a.y-b); }
	friend _INLINE V operator -(T a,const V &b) { return V(a-b.x,a-b.y); }
	friend _INLINE V operator *(const V &a,const V &b) { return V(a.x*b.x,a.y*b.y); }
	friend _INLINE V operator *(const V &a,T s) { return V(a.x*s,a.y*s); }
	friend _INLINE V operator *(T s,const V &a) { return V(a.x*s,a.y*s); }
	friend _INLINE V operator /(const V &a,const V &b) { return V(b.x?a.x/b.x:0,b.y?a.y/b.y:0); }
	friend _INLINE V operator /(const V &a,T s) { return (s!=0)?V(a.x/s,a.y/s):V(0,0); }
	friend _INLINE V operator /(T s,const V &a) { return V(a.x?s/a.x:0,a.y?s/a.y:0); }
	friend _INLINE const V &operator +=(V &a,const V &b) { a.x+=b.x; a.y+=b.y; return a; }
	friend _INLINE const V &operator +=(V &a,T b) { a.x+=b; a.y+=b; return a; }
	friend _INLINE const V &operator -=(V &a,const V &b) { a.x-=b.x; a.y-=b.y; return a; }
	friend _INLINE const V &operator -=(V &a,T b) { a.x-=b; a.y-=b; return a; }
	friend _INLINE const V &operator *=(V &a,const V &b) { a.x*=b.x; a.y*=b.y; return a; }
	friend _INLINE const V &operator *=(V &a,T s) { a.x*=s; a.y*=s; return a; }
	friend _INLINE const V &operator /=(V &a,const V &b) { a.x=b.x?a.x/b.x:0; a.y=b.y?a.y/b.y:0; }
	friend _INLINE const V &operator /=(V &a,T s) { if(s!=0) { a.x/=s; a.y/=s; } else { a.x=0; a.y=0; } return a; }
	friend _INLINE bool operator ==(const V &a,const V &b) { return (a.x==b.x)&&(a.y==b.y); }
#else
    _INLINE V operator -() const { return V(-x,-y); }
	_INLINE V operator +(const V &v) const { return V(x+v.x,y+v.y); }
	_INLINE V operator -(const V &v) const { return V(x-v.x,y-v.y); }
	_INLINE V operator *(T s) const { return V(x*s,y*s); }
	_INLINE V operator /(T s) const { return (s!=0)?V(x/s,y/s):V(0,0); }
	_INLINE void operator +=(const V &v) { x+=v.x; y+=v.y; }
	_INLINE void operator -=(const V &v) { x-=v.x; y-=v.y; }
	_INLINE void operator *=(T s) { x*=s; y*=s; }
	_INLINE void operator /=(T s) { if(s==0) x=0, y=0; else x/=s, y/=s; }
	_INLINE bool operator ==(const V &v) const { return (x==v.x)&&(y==v.y); }
#endif

	_INLINE bool all_lequal(const V &v) const { return (x<=v.x)&&(y<=v.y); }
	_INLINE bool all_gequal(const V &v) const { return (x>=v.x)&&(y>=v.y); }

	_INLINE bool in_box(const V &bmin,const V &bmax) const { return bmin.x<=x && x<=bmax.x && bmin.y<=y && y<=bmax.y; }


	_INLINE T length()		const { return sqrt(dot(*this)); }
	_INLINE T length2()	const { return dot(*this); }

	_INLINE void normalize()
	{
		T len = length();
		if(!len) return;
		x/=len; y/=len;
	}

	_INLINE V get_normalized() const
	{
		V v = *this;
		v.normalize();
		return v;
	}

	_INLINE void rotate90() const
	{
		*this = V(y,-x);
	}

	_INLINE V get_rotated90() const
	{
		return V(y,-x);
	}

	_INLINE float dot(const V &v) const { return x*v.x+y*v.y; }
	_INLINE T cross(const V &v) const { return x*v.y-y*v.x; }

	_INLINE void set_mins(const V &v)
	{
		if(v.x<x) x=v.x;
		if(v.y<y) y=v.y;
	}

	_INLINE void set_maxs(const V &v)
	{
		if(v.x>x) x=v.x;
		if(v.y>y) y=v.y;
	}

	_INLINE void scale_xy(const V &v) { x*=v.x; y*=v.y; }
	_INLINE V get_scaled_xy(const V &v) const { return V(x*v.x,y*v.y); }

	_INLINE void update_min_max(V &min,V &max) const
	{
		if(x<min.x) min.x=x;
		if(y<min.y) min.y=y;
		if(x>max.x) max.x=x;
		if(y>max.y) max.y=y;
	}

	_INLINE void saturate()
	{
		if(x<0) x = 0;
		if(x>1) x = 1;
		if(y<0) y = 0;
		if(y>1) y = 1;
	}

};

typedef vector2d<float> vec2;
typedef vector2d<int> ivec2;


template<class T>
struct vector4d {
	typedef vector4d<T> V;

	T x,y,z,w;
	
	_INLINE vector4d() {}
	_INLINE vector4d(T _x,T _y,T _z,T _w) : x(_x), y(_y), z(_z), w(_w) {}

	// 2D mapping: pos' = pos*xy + wz
	void make_map_to_unit(const vector2d<T> &bmin,const vector2d<T> &bmax);
	void make_map_unit_to(const vector2d<T> &bmin,const vector2d<T> &bmax);
	void make_map_to_view(const vector2d<T> &bmin,const vector2d<T> &bmax);
	void make_map_view_to(const vector2d<T> &bmin,const vector2d<T> &bmax);
	void make_map_concat(const V &a,const V &b);
	void make_map_inverse(const V &a);
	void make_map_box_scale_fit(const vector2d<T> &box,const vector2d<T> &space,const vector2d<T> &align);
	vector2d<T>  map_apply(const vector2d<T> &p)		{ return vector2d<T>(p.x*x+w,p.y*y+z); }
	vector2d<T>  map_inv_apply(const vector2d<T> &p)	{ return vector2d<T>((p.x-w)/x,(p.y-z)/y); }
};

typedef vector4d<float> vec4;
typedef vector4d<int> ivec4;


template<class T> void vector4d<T>::make_map_to_unit(const vector2d<T> &bmin,const vector2d<T> &bmax)
{
	// P' = (P-bmin)/(bmax-bmin)
	x = 1.f/(bmax.x - bmin.x);
	y = 1.f/(bmax.y - bmin.y);
	w = -bmin.x*x;
	z = -bmin.y*y;
}

template<class T> void vector4d<T>::make_map_unit_to(const vector2d<T> &bmin,const vector2d<T> &bmax)
{
	// P' = P*(bmax-bmin) + bmin
	x = bmax.x - bmin.x;
	y = bmax.y - bmin.y;
	w = bmin.x;
	z = bmin.y;
}

template<class T> void vector4d<T>::make_map_to_view(const vector2d<T> &bmin,const vector2d<T> &bmax)
{
	// P' = ((P-bmin)/(bmax-bmin))*vector2d<T>(2,-2) + vector2d<T>(-1,1) = P/(bmax-bmin)*vector2d<T>(2,-2) - bmin/(bmax-bmin)*vector2d<T>(2,-2) + vector2d<T>(-1,1)
	x = 2.f/(bmax.x - bmin.x);
	y = 2.f/(bmin.y - bmax.y);
	w = -1.f - bmin.x*x;
	z =  1.f - bmin.y*y;
}

template<class T> void vector4d<T>::make_map_view_to(const vector2d<T> &bmin,const vector2d<T> &bmax)
{
	// P' = (P*vector2d<T>(.5,-.5)+vector2d<T>(.5,.5))*(bmax-bmin) + bmin = P*vector2d<T>(.5,-.5)*(bmax-bmin)+vector2d<T>(.5,.5)*(bmax-bmin) + bmin
	x = .5f*(bmax.x - bmin.x);
	y = .5f*(bmin.y - bmax.y);
	w = bmin.x + x;
	z = bmin.y - y;
}

template<class T> void vector4d<T>::make_map_concat(const vector4d<T> &a,const vector4d<T> &b)
{
	// P' = (P*a.xy + a.wz)*b.xy + b.wz = P*a.xy*b.xy + a.wz*b.xy + b.wz
	// target can't alias with b
	x = a.x*b.x;
	y = a.y*b.y;
	w = a.w*b.x + b.w;
	z = a.z*b.y + b.z;
}

template<class T> void vector4d<T>::make_map_inverse(const vector4d<T> &a)
{
	// P' = (P-a.wz)/a.xy
	x = 1.f/a.x;
	y = 1.f/a.y;
	w = -a.w*x;
	z = -a.z*y;
}

template<class T> void vector4d<T>::make_map_box_scale_fit(const vector2d<T> &box,const vector2d<T> &space,const vector2d<T> &align)
{
	x = space.x/box.x;
	y = space.y/box.y;
	if(x<y) x=y; else y=x;
	w = (space.x-box.x*x)*align.x;
	z = (space.y-box.y*y)*align.y;
}



#if 0
struct quat4 : public D3DXQUATERNION {

	_INLINE quat4() {}
	_INLINE quat4(float _x,float _y,float _z,float _w) : D3DXQUATERNION(_x,_y,_z,_w) {}

	_INLINE void SetIdentity()				{ D3DXQuaternionIdentity(this); }
	_INLINE void SetRotationX(float ang)	{ D3DXQuaternionRotationYawPitchRoll(this,0,ang*float(M_PI/180.f),0); }
	_INLINE void SetRotationY(float ang)	{ D3DXQuaternionRotationYawPitchRoll(this,ang*float(M_PI/180.f),0,0); }
	_INLINE void SetRotationZ(float ang)	{ D3DXQuaternionRotationYawPitchRoll(this,0,0,ang*float(M_PI/180.f)); }

	_INLINE void SetRotationYPR(float yaw,float pitch,float roll)
	{
		quat4 y,p,r;
		D3DXQuaternionRotationAxis(&y,(const D3DXVECTOR3*)&vec3(0,0,1),yaw*float(M_PI/180.f));
		D3DXQuaternionRotationAxis(&p,(const D3DXVECTOR3*)&vec3(0,1,0),-pitch*float(M_PI/180.f));
		D3DXQuaternionRotationAxis(this,(const D3DXVECTOR3*)&vec3(1,0,0),roll*float(M_PI/180.f));
		*this *= p;
		*this *= y;
	}

	_INLINE vec3 Transform(const vec3 &v)
	{
		D3DXQUATERNION _v(v.x,v.y,v.z,0);
		_v = D3DXQUATERNION(-x,-y,-z,w) * _v;
		_v *= *this;
		return vec3(_v.x,_v.y,_v.z);
	}
};



struct matrix4x4 : public D3DXMATRIX {

	_INLINE vec3 Apply(const vec3 &v) const
	{
		float out[4];
		D3DXVec3Transform((D3DXVECTOR4*)out,(D3DXVECTOR3*)&v,this);
		return *(vec3*)out;
	}

	_INLINE vec3 Unapply(const vec3 &v) const
	{
		vec3 t, out;
//		out.x = v.x*_11 + v.y*_21 + v.z*_31 + _41;
//		out.y = v.x*_12 + v.y*_22 + v.z*_32 + _42;
//		out.z = v.x*_13 + v.y*_23 + v.z*_33 + _43;

		t.x = v.x - _41;
		t.y = v.y - _42;
		t.z = v.z - _43;

		out.x = t.x*_11 + t.y*_12 + t.z*_13;
		out.y = t.x*_21 + t.y*_22 + t.z*_23;
		out.z = t.x*_31 + t.y*_32 + t.z*_33;
		return out;
	}

	_INLINE void ApplyInPlaceVec4(float *v) const
	{
		D3DXVECTOR4 out;
		D3DXVec4Transform(&out,(D3DXVECTOR4*)v,this);
		*((D3DXVECTOR4*)v) = out;
	}

	_INLINE void SetIdentity()							{ D3DXMatrixIdentity(this); }
	_INLINE void SetRotationFromQuat(const quat4 &q)	{ D3DXMatrixRotationQuaternion(this,&q); }

	_INLINE void SetAffineTransform(const vec3 &trans,const quat4 &rot,const vec3 &scale)
	{
		D3DXMatrixTransformation(this,NULL,NULL,(D3DXVECTOR3*)&scale,NULL,&rot,(D3DXVECTOR3*)&trans);
	}

	_INLINE void Transpose()
	{
		matrix4x4 tmp;
		D3DXMatrixTranspose(&tmp,this);
		*this = tmp;
	}

	_INLINE void Inverse()
	{
		matrix4x4 tmp;
		D3DXMatrixInverse(&tmp,NULL,this);
		*this = tmp;
	}
};

struct plane4 {
	vec3	normal;
	float	offs;

	_INLINE void MakeFromPoints(const vec3 &p1,const vec3 &p2,const vec3 &p3)
	{
		normal = (p2-p1).cross(p3-p1);
		normal.normalize();
		offs = normal.dot(p1);
	}

	_INLINE void Normalize()
	{
		float len = normal.length();
		if(len!=0)
		{
			len = 1.f/len;
			normal *= len;
			offs *= len;
		}
	}
};
#endif


}



#undef _INLINE



#endif
