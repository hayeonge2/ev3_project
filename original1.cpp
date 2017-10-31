#include "h_crane.h"


class Crain : public CraneCrane
{
private:
    //ultrasonic sensor declaration 
    ev3dev::ultrasonic_sensor ultra_q;
    //touch sensor declaration
    ev3dev::touch_sensor touch_q;
    ev3dev::motor a;
    ev3dev::motor b; 
    ev3dev::motor c;
    
public:
    // Hardware Configuration
    // when we want to use a sensor, need to say where it is connected --> here
    Crain():m_speed(0), touch_q(ev3dev::INPUT_2), a(ev3dev::OUTPUT_B), b(ev3dev::OUTPUT_C), c(ev3dev::OUTPUT_A), ultra_q(ev3dev::INPUT_3)
    {
        
    }
    
    int m_speed;
    
    /* for touch sensor activation
    // A boolean indicating whether the current touch sensor is being
    // pressed.
    bool is_pressed(bool do_set_mode = true) {
    if (do_set_mode) set_mode(mode_touch);
    return value(0);
    }
    */
    
    bool get_touch_pressed()
    {
        return touch_q.is_pressed();
    }
    
    /* for ultrasonic sensor activation
    // Measurement of the distance detected by the sensor,
    // in centimeters.
    float distance_centimeters(bool do_set_mode = true) {
    if (do_set_mode) set_mode(mode_us_dist_cm);
    return float_value(0);
    */
    
    float get_ultrasonic_distance()
    {
        return ultra_q.distance_centimeters();
    }
    
    virtual bool get_down()
    {
        return m_down; //return true for get_down
    }

    virtual bool get_up()
    {
        return m_up;
    }

    virtual bool get_right()
    {
        return m_right;
    }

    virtual bool get_left()
    {
        return m_left;
    }

    virtual bool get_enter()
    {
        return m_enter;
    }

    virtual bool get_escape()
    {
        return m_escape;
    }

    virtual int  get_speed()
    {
        return 100;
    }
    
    virtual int a_get_position_sp()
    {
        return 100;
    }
    
    virtual int b_get_position_sp()
    {
        return 350;
    }
    
    virtual int c_get_position_sp()
    {
        return 30;
    }
    
    virtual void set_down(bool val)
    {
        m_down = val;
    }
    
    virtual void set_up(bool val)
    {
        m_up = val;    
    }
    
    virtual void set_right(bool val)
    {
        m_right = val;   
    }
    virtual void set_left(bool val)
    {
        m_left = val; 
    } 
    
    virtual void set_enter(bool val)
    {
        m_enter = val;    
    }
    
    virtual void set_escape(bool val)
    {
        m_escape = val;    
    }
    
    virtual void set_speed(int val)
    {
        m_speed = val;    
    }
    
public:
    void example_code();
};

void Crain::example_code()
{ //This function is for example, you should develop your own logics
    set_down(ev3dev::button::down.pressed());
    set_up(ev3dev::button::up.pressed());
    set_right(ev3dev::button::right.pressed());
    set_left(ev3dev::button::left.pressed());
    set_escape(ev3dev::button::back.pressed());
    set_enter(ev3dev::button::enter.pressed());
    
    /*
    while (1)
    {
        float a = 0 ;
        a = ultra_q.distance_centimeters();
        std::cout << a << std::endl;
    }
    */
    
    a.reset();
       
    b.reset(); 
    
    while(abs(a.position()) != abs(a_get_position_sp()))
    {
        
        while(abs(b.position()) != abs(b_get_position_sp()))
        {
            if(ultra_q.distance_centimeters() == 5)
            {
                a.set_speed_sp(get_speed());
                a.set_position_sp(-1*a_get_position_sp());
                a.run_to_abs_pos();
                a.set_stop_action("hold");
                a.stop();
            }
        
            b.set_speed_sp(get_speed());
            b.set_position_sp(-1*b_get_position_sp());
            b.run_to_abs_pos();
            b.set_stop_action("hold");
            b.stop();
        }

    }
    /*
    }
    
    b.reset();
    
    while(abs(b.position()) != abs(b_get_position_sp()))
    {
        b.set_speed_sp(get_speed());
        b.set_position_sp(-1*b_get_position_sp());
        b.run_to_abs_pos();
        b.set_stop_action("hold");
        b.stop();
    }
    
        
    a.reset();
        
    while(abs(a.position()) != abs(a_get_position_sp()))
    {
        a.set_speed_sp(get_speed());
        a.set_position_sp(-1*a_get_position_sp());
        a.run_to_abs_pos();
        a.set_stop_action("hold");
        a.stop();
    }
    
    
    c.reset();
    
    while(abs(c.position()) != abs(c_get_position_sp()))
    {
        c.set_speed_sp(get_speed());
        c.set_position_sp(-1*c_get_position_sp());
        c.run_to_abs_pos();
        c.set_stop_action("hold");
        c.stop();
    }
*/
    a.stop();
    b.stop();
}

int main()
{     
    Crain crain;
    while(true){
        
        
        if(crain.get_touch_pressed()==true){ 
            
        crain.example_code(); //This line is for example, you should erase this ex_code in your 'real code' 
  
        }
    }
}