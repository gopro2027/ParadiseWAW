namespace myMath {
	#define PI (3.1415926535897931)
float abs(float a) {
	if (a < 0)
		return a*-1;
	return a;
}
float DegreesToRadians(float Degrees)
{
    return Degrees * PI / 180.0f;
}
 
float RadiansToDegrees(float Radians)
{
    return Radians * 180.0f / PI;
}
 
float pow(float num, int power) {
    float ret = 1;
    for (int i = 0; i < power; i++)
        ret = ret*num;
    return ret;
}
 
float root(float num, int nroot) {
    int iterations = 15 * (nroot-1);
    float x = iterations*100;
    for (int i = 1; i < iterations; i++) {
       x = (float)(((float)1/nroot)*(((nroot-1)*x)+(num/pow(x,nroot-1))));
    }
    return x;
}
 
float sin(float deg) {
    bool neg = false;
    while (deg >= 360) deg = deg - 360;
    while (deg < 0) deg = deg + 360;
    if (deg > 180) {
        deg = deg - 180;
        neg = true;
    }
    float ret = (float)(4*deg*(180-deg))/(40500-(deg*(180-deg)));
    if (neg)return ret*-1;
    return ret;
}
 
float cos(float AnglesDeg)
{
 float AnglesRad = DegreesToRadians(AnglesDeg);
 float Rad = (float)(PI/2.0f)-AnglesRad;
 float ang = RadiansToDegrees(Rad);
    return sin(ang);
}
 
float tan(float AnglesDeg)
{
    float sinus = sin(AnglesDeg);
    float cosinus = cos(AnglesDeg);
    return sinus/cosinus;
}

double atan(double x, int n)
{
	double a = 0.0;// 1st term
	double sum = 0.0;

	// special cases
	if( x == 1.0 ) return PI/4.0;
	if( x == -1.0 ) return -PI/4.0;

	if(n > 0)
	{
	    if( (x < -1.0) || (x > 1.0) )
	    {
	        // constant term
	        if( x > 1.0 )
                sum = PI/2.0;
            else
                sum = -PI/2.0;
            // initial value of a
            a = -1.0/x;
            for(int j=1; j<=n; j++)
            {
                sum += a;
                a *= -1.0*(2.0*j-1)/((2.0*j+1)*x*x);// next term from last
            }
	    }
	    else// -1 < x < 1
	    {
	        // constant term
	        sum = 0.0;
	        // initial value of a
            a = x;
            for(int j=1; j<=n; j++)
            {
                sum += a;
                a *= -1.0*(2.0*j-1)*x*x/(2.0*j+1);// next term from last
            }
	    }
		//r_err = a;// max. error = 1st term not taken for alternating series
	}

	return sum;
}

double atan2(double y, double x)
{
    double u = atan( y/x, 24);
    if( x < 0.0 )// 2nd, 3rd quadrant
    {
        if( u > 0.0 )// will go to 3rd quadrant
            u -= PI;
        else
            u += PI;
    }
    return u;
}


}
