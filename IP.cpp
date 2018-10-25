#include <iostream>

using namespace std;

void binaryPrint(int x)  // procedure for printing 8-bit numbers in binary form
{
    int bin[8];
    for(int i=0;i<8;i++)
    {
        bin[i]=x & 1;
        x>>=1;
    }                                                        //calculation of number in net
    for(int i=7;i>=0;i--)
        cout<<bin[i];
 }

 void hexPrint(int x)  // procedure for printing 8-bit numbers in hex form
{
    int t=x/16,q=x%16;
    if (t>9)
        cout<<(char)('A'+ t-10);
    else
        cout<<t;
    if (q>9)
        cout<<(char)('A'+ q-10);
    else
        cout<<q;
 }

struct Address                                                            //structure for working with addresses
{
    int *bytes;                                                           //array for 4 numbers

    Address(int byte1,int byte2,int byte3,int byte4): bytes(new int[4])   //constructor from 4 integers
    {
        bytes[0]=byte1;
        bytes[1]=byte2;
        bytes[2]=byte3;
        bytes[3]=byte4;
    }

    Address(const Address& other): bytes(new int[4])                  //copying constructor
    {
        for(int i=0;i<4;i++)
            bytes[i]=other.bytes[i];
    }

    ~Address()                                                        //destructor
    {
        delete[] bytes;
    }

    Address& operator=(const Address& other)                          //assignment operator
    {
        if(this != &other)
        {
            if(bytes)
                delete[] bytes;
            bytes = new int[4];
            for(int i=0;i<4;i++)
                bytes[i]=other.bytes[i];
        }
        return *this;
    }

    Address& operator&=(const Address& other)                         //Bitwise AND assignment
    {
        bytes[0]&=other.bytes[0];
        bytes[1]&=other.bytes[1];
        bytes[2]&=other.bytes[2];
        bytes[3]&=other.bytes[3];
        return *this;
    }


    Address& operator|=(const Address& other)                         //Bitwise OR assignment
    {
        bytes[0]|=other.bytes[0];
        bytes[1]|=other.bytes[1];
        bytes[2]|=other.bytes[2];
        bytes[3]|=other.bytes[3];
        return *this;
    }


    Address& operator^=(const Address& other)                         //Bitwise XOR assignment
    {
        bytes[0]^=other.bytes[0];
        bytes[1]^=other.bytes[1];
        bytes[2]^=other.bytes[2];
        bytes[3]^=other.bytes[3];
        return *this;
    }

    void ipBinaryPrint()                                            //method for printing address in binary form
    {
        binaryPrint(bytes[0]);
        cout<<".";
        binaryPrint(bytes[1]);
        cout<<".";
        binaryPrint(bytes[2]);
        cout<<".";
        binaryPrint(bytes[3]);
    }

        void ipHexPrint()                                            //method for printing address in binary form
    {
        hexPrint(bytes[0]);
        cout<<".";
        hexPrint(bytes[1]);
        cout<<".";
        hexPrint(bytes[2]);
        cout<<".";
        hexPrint(bytes[3]);
    }

const Address& operator++()                                         //prefix increment
{
        if(bytes[3]==255){
                bytes[3]=0;
                if(bytes[2]==255){
                    bytes[2]=0;
                    if(bytes[1]==255){
                            bytes[1]=0;
                            if(bytes[0]==255)
                            {
                                bytes[0]=0;
                            }
                            else bytes[0]++;
                    }
                    else bytes[1]++;
                }
                 else bytes[2]++;
        }
        else bytes[3]++;
    return *this;
}

const Address& operator--()                                         //prefix decrement
{
        if(bytes[3]==0)
        {
                bytes[3]=255;
                if(bytes[2]==0)
                {
                    bytes[2]=255;
                    if(bytes[1]==0)//calculation of net address
                    {
                            bytes[1]=255;
                            if(bytes[0]==0)
                            {
                                bytes[0]=255;
                            }
                            else bytes[0]--;
                    }
                    else bytes[1]--;
                }
                 else bytes[2]--;
        }
        else bytes[3]--;
    return *this;
}

};

const Address operator++(Address& addressforincrement,int)          //postfix increment
{
    Address oldValue(addressforincrement);
    ++addressforincrement;
    return Address(oldValue);
}

const Address operator--(Address& addressfordecrement,int)          //postfix decrement
{
    Address oldValue(addressfordecrement);
    --addressfordecrement;
    return Address(oldValue);
}

ostream& operator << (ostream &s, const Address &addressforprint)   //output stream
{
	s << addressforprint.bytes[0] << "." << addressforprint.bytes[1]
	  << "." << addressforprint.bytes[2] << "." <<addressforprint.bytes[3];
	return s;
}

istream& operator >> (istream &s, Address &addressforread)          //input stream
{
    int firstbyte = 0 , secondbyte = 0, thirdbyte = 0, forthbyte =0;
    s >> firstbyte >> secondbyte >> thirdbyte >> forthbyte;
    addressforread = Address(firstbyte,secondbyte,thirdbyte,forthbyte);
    return s;
}
const Address operator&(const Address& first, const Address& other) //bitwise AND
{
    Address temp(first);
    return temp &= other;

}

const Address operator|(const Address& first, const Address& other) //bitwise OR
{
    Address temp(first);
    return Address(first) |= other;

}

const Address operator^(const Address& first, const Address& other) //bitwise XOR
{
    Address temp(first);
    return Address(first) ^= other;

}

const Address operator~(const Address& other)                       //bitwise NOT
{
    return Address( 255 - other.bytes[0], 255 - other.bytes[1] , 255 - other.bytes[2], 255 - other.bytes[3]);
}

bool operator==(const Address& first, const Address& second)        //Equal to
{
    return ((first.bytes[0]==second.bytes[0]) &&
        (first.bytes[1]==second.bytes[1]) &&
        (first.bytes[2]==second.bytes[2]) &&
        (first.bytes[3]==second.bytes[3]));
}

bool operator!=(const Address& first, const Address& second)                //Not equal to
{
    return !(first==second);
}


struct IpAddress                                                            //structure for working with ip's and masks
{
    Address ip;
    Address mask;
    IpAddress(int ipbyte1, int ipbyte2, int ipbyte3, int ipbyte4,           //constructor
             int maskbyte1,int maskbyte2,int maskbyte3,int maskbyte4):
                    ip(ipbyte1, ipbyte2, ipbyte3, ipbyte4),
                    mask(maskbyte1, maskbyte2, maskbyte3, maskbyte4)
    { }



    Address getNetIp()                                                      //calculation of net address
    {
        return ip&mask;
    }


    int getNumber()                                                         //calculation of number in net
    {
        Address number=ip&(~mask);
        return number.bytes[3]+255*(number.bytes[2]+255*(number.bytes[1]+255*number.bytes[0]));
    }
};

int main()                                                                      //examples
{
    IpAddress A(192,168,255,128,255,255,192,0);

    cout << "A ip:             " << A.ip         << endl
         << "A mask:           " << A.mask       << endl
         << "A net IP:         " << A.getNetIp() << endl
         << "A number in net:  " << A.getNumber()<< endl;

    IpAddress B(192,192,240,128,255,255,192,0);

    cout << "B ip:             " << B.ip         << endl
         << "B mask:           " << B.mask       << endl
         << "B net IP:         " << B.getNetIp() << endl
         << "B number in net:  " << B.getNumber()<< endl;

    cout << "A&B ip:           "<< ((A.ip) & (B.ip))<< endl
         << "A|B ip:           "<< ((A.ip) | (B.ip)) <<endl
         << "A^B ip:           "<< ((A.ip) ^ (B.ip)) <<endl;

    IpAddress C(A);

    cout << "C ip:             " << A.ip         << endl
         << "C mask:           " << A.mask       << endl;

    if(C.ip==B.ip) cout<<"C equal B, by ip"<<endl;
    if(A.ip==B.ip) cout<<"A equal B, by ip"<<endl;
    if(A.ip==C.ip) cout<<"A equal C, by ip"<<endl;

    if(C.mask==B.mask) cout<<"C equal B, by mask"<<endl;
    if(A.mask==B.mask) cout<<"A equal B, by mask"<<endl;
    if(A.mask==C.mask) cout<<"A equal C, by mask"<<endl;

    if(C.ip!=B.ip) cout<<"C not equal B, by ip"<<endl;
    if(A.ip!=B.ip) cout<<"A not equal B, by ip"<<endl;
    if(A.ip!=C.ip) cout<<"A not equal C, by ip"<<endl;

    if(C.mask!=B.mask) cout<<"C not equal B, by mask"<<endl;
    if(A.mask!=B.mask) cout<<"A not equal B, by mask"<<endl;
    if(A.mask!=C.mask) cout<<"A not equal C, by mask"<<endl;
    {
        cout<<"A ip in binary form:  ";
        A.ip.ipBinaryPrint();
        cout<<endl;
    }
        {
        cout<<"A ip in hex form:  ";
        A.ip.ipHexPrint();
        cout<<endl;
    }
    cout << "prefix++ for C ip: " << ++C.ip   << endl;
    cout << "C after prefix++:  " << C.ip     << endl;
    cout << "postfix++ for C ip:" << C.ip++   << endl;
    cout << "C after postfix++: " << C.ip     << endl;
    cout << "prefix-- for C ip: " << --(C.ip) << endl;
    cout << "C after prefix--:  " << C.ip     << endl;
    cout << "postfix-- for C ip:" << C.ip--   << endl;
    cout << "C after prefix--:  " << C.ip     << endl;

    Address X(255,255,255,255);
    Address Y(0,0,0,0);
    cout << "Increment/Decrement on the edge" <<endl << ++X << " vs " << --Y << endl;
    return 0;
}
