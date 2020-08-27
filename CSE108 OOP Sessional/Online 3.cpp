#include<iostream>
#include<cmath>

using namespace std;

/*******************************Online 3***********************************************/
/* In this assignment, you will be dealing with complex numbers in an object oriented */
/* way. There are 4 parts of the assignment.                                          */
/* At first, read the following class complex_number carefully. After that move on to */
/* the main function where each part of the assignment is described separately.       */
/*                         Time : 40 minutes                                          */
/**************************************************************************************/




/* The following class represents complex number in mathematics.             */
/* You are not allowed to change the access modifier of any member variable. */
/* You are not allowed to add any new member variable.                       */


class complex_number {

    double real;
    double imaginary;

public:
    complex_number(double r=0, double i=0) { real = r; imaginary = i;}

	/* A utility function to facilitate printing the complex number in a + bi format. */
	/*  You should not modify this function.                                          */
    friend ostream &operator<<(ostream  &os, const complex_number &cn) {
        if (!(cn.real || cn.imaginary)) return (os<<0);
        if(cn.real) os<<cn.real;
        if(cn.real && cn.imaginary) os<<(cn.imaginary>0?" + ":" - ");
        if(cn.imaginary) os<<(cn.real?abs(cn.imaginary):cn.imaginary)<<"i";
        return os;
    }
};


/* Following is the main function. You can find out the task requirements for this assignment there.                 */
/* For your convenience, the expected output of each cout statement is written as a comment alongside the statement. */
/* You should not write or modify any code in this function other than for testing purpose. Even if you do so,       */
/* make sure to remove your modifications before evaluation. Otherwise, you may not see the expected outputs.        */

int main() {

/*****************************Part 1***********************************/
/* You do not need to write any code for this part. Just build and    */
/* run the code to understand the definition of class complex_number. */
/* Notice that, you can easily print a complex number just by passing */
/* it to cout.                                                        */
/**********************************************************************/
    complex_number z1(1,2);
    cout<<z1<<endl; // 1 + 2i

	complex_number z2(4,3),z3,z4;

/******************************Part 2**********************************/
/* In this part you are required to write necessary code segments to  */
/* facilitate usual arithmetic operations of complex numbers.         */
/* Add necessary code so that the following expressions compiles and  */
/* the value of z3 and z4 are updated accordingly                     */
/* (It is assumed that you have the required mathematical background) */
/**********************************************************************/
/*
	z3 = -z1 + (2.5*z2);
    cout<<z3<<endl; // 9 + 5.5i
    z4 = z2 * z1;
    cout<<z4<<endl; // -2 + 11i
*/


/******************************Part 3**********************************/
/* Following are some unconventional functionalities you need to      */
/* implement for this assignment. The expected behaviour of each      */
/* operation is commented alongwith.                                  */
/**********************************************************************/
/*
	z1++; // Increment the imaginary part by 1
    cout<<z1<<endl; // 1 + 3i
    ++z2; // Increment the real part by 1
    cout<<z2<<endl; // 5 + 3i
    z3--; // Decrement the imaginary part by 1
    cout<<z3<<endl; // 9 + 4.5i
    --z4; // Decrement the real part by 1
    cout<<z4<<endl; // -3 + 11i
*/

/******************************Part 4**********************************/
/* Two complex numbers are considered equal if and only if            */
/* their real parts are equal and imaginary parts are equal. Write    */
/* down necessary code so that the following code segment compiles.   */
/**********************************************************************/

/*
    if( ((z4+z1)-(z3*1.4)) == complex_number(-14.6,7.7) )
        cout<<"You have successfully completed all the tasks!"<<endl;
*/
	return 0;
}

