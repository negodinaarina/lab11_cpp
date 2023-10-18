#include <iostream>
#include <string>
using namespace std;

class Time{
public:
    int hours, minutes, seconds, seconds_in_day;
    class TimeError{
        string message;
    public:
        TimeError(){message="Something went wrong...";}
        void printMessage(){cout << message << endl;}
    };
    Time(){
        hours = 0;
        minutes = 0;
        seconds = 0;
        seconds_in_day = 0;
    }
    Time(int h, int m, int s){
        if(s < 0){
            s += 60;
            m -= 1;
        }
        if(m < 0){
            m += 60;
            h -= 1;
        }
        if(h < 0){
            throw TimeError();
        }
        m += s / 60;
        s %= 60;
        h += m / 60;
        m %= 60;
        hours = h;
        minutes = m;
        seconds = s;
        seconds_in_day = hours*3600 + minutes*60 + seconds;
    }
    void printTime() const{
        cout << hours << ":" << minutes << ":" << seconds << endl;
    }
    static Time sumTimes(Time t1, Time t2){
        Time t3 = Time(t1.hours + t2.hours, t1.minutes + t2.minutes, t1.seconds + t2.seconds);
        return t3;
    }

// Перегружаем бинарный оператор сложения, передаем в качестве второго аргумента объект
// класса Time, складываем часы, минуты и секунды. Проверку на выход за границы
// осуществлять не нужно, так как она происходит при создании объекта класса в конструкторе
    Time operator + (const Time& time) const{
        return Time{hours + time.hours, minutes + time.minutes, seconds + time.seconds};
    }

// Перегружаем бинарный оператор вычитания, в качестве второго аргумента передаем
// объект класса Time, вычитаем часы, минуты, секунды. Проверку на выход за границу
// нуля осуществлять не нужно, она происходит в конструкторе.
    Time operator - (const Time& time) const{
        return Time{hours - time.hours, minutes - time.minutes, seconds - time.seconds};
    }

//Перегружаем оператор сложение объекта Time и целого числа - количества секунд.
//Сначала выделяем часы, потом минуты и остаток - секунды.
    Time operator + (int sec) const{
        int new_hours = hours + sec / 3600;
        sec%=3600;
        int new_minutes = minutes + sec / 60;
        sec%=60;
        int new_seconds = seconds + sec;
        return Time{new_hours, new_minutes, new_seconds};
    }
// Перегружаем 4 оператора сравнения - они возвращают логическое значение.
    bool operator ==(const Time& time) const{
        return seconds_in_day == time.seconds_in_day;
    }

    bool operator <(const Time& time) const{
        return seconds_in_day < time.seconds_in_day;
    }

    bool operator >(const Time& time) const{
        return seconds_in_day > time.seconds_in_day;
    }

    bool operator !=(const Time& time) const{
        return seconds_in_day != time.seconds_in_day;
    }
};

//Перегружаем оператор сложение целого числа(количества секунд) и объекта Time.
//Делаем также, как и в предыдущем пункте, но теперь передаем два аргумента в функцию.
Time operator + (int sec, const Time& time)
{
    int new_hours = time.hours + sec / 3600;
    sec%=3600;
    int new_minutes = time.minutes + sec / 60;
    sec%=60;
    int new_seconds = time.seconds + sec;
    return Time{new_hours, new_minutes, new_seconds};
}

int main(){
    try{
        Time t1(2, 40, 40);
        Time t2(1, 34, 70);
        Time t3 = t1 + t2;
        t1.printTime();
        t2.printTime();
        t3.printTime();
        Time t4 = t2 + 3600;
        t4.printTime();
        cout << (t1 < t2);
        Time t5 = 60 + t4;
        t5.printTime();
    }
    catch(Time::TimeError& error){
        error.printMessage();
    }
}