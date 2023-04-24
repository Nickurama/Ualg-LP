class TrafficLight
{
    final private color DARK_GREY = color(128, 128, 128);
    final private color RED = color(255, 0, 0);
    final private color YELLOW = color(255, 255, 0);
    final private color GREEN = color(0, 255, 0);
    
    final private int TRANSITION_TIME_TICKS = 60;
    
    private Light redLight;
    private Light yellowLight;
    private Light greenLight;
    
    private int timerTicks;
    private Light nextLight;
    
    public float x;
    public float y;
    public float width;
    public float height;
    public float rotationAngle;
    
    public TrafficLight(float x, float y, float width, float rotationAngle)
    {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = width * 3;
        this.rotationAngle = -rotationAngle;
        timerTicks = 0;
        
        // redLight = new Light(this.x + cos(radians(rotationAngle)) * (width / 2) + (height / 6 * 1) * cos(radians(rotationAngle)), this.y + sin(radians(rotationAngle)) * (height / 6 * 1) + sin(radians(rotationAngle)) * (width / 2), width / 2, RED);
        redLight = new Light(0, -(this.height / 6 * 2), width / 2, RED);
        redLight.turnON();
        // yellowLight = new Light(this.x + cos(radians(rotationAngle)) * (width / 2) + (height / 6 * 3) * cos(radians(rotationAngle)), this.y + sin(radians(rotationAngle)) * (height / 6 * 3) + sin(radians(rotationAngle)) * (width / 2), width / 2, YELLOW);
        yellowLight = new Light(0, 0, width / 2, YELLOW);
        yellowLight.turnOFF();
        // greenLight = new Light(this.x + cos(radians(rotationAngle)) * (width / 2) + (height / 6 * 5) * cos(radians(rotationAngle)), this.y + sin(radians(rotationAngle)) * (height / 6 * 5) + sin(radians(rotationAngle)) * (width / 2), width / 2, GREEN);
        greenLight = new Light(0,(this.height / 6 * 2), width / 2, GREEN);
        
        greenLight.turnOFF();
    }
    
    public void draw()
    {
        update();
        pushMatrix();
        fill(DARK_GREY);
        rectMode(CENTER);
        translate(x, y);
        rotate(radians(rotationAngle));
        rect(0, 0, width, height);
        redLight.draw();
        yellowLight.draw();
        greenLight.draw();
        popMatrix();
    }
    
    private void update()
    {
        if (timerTicks == 0 && yellowLight.isON())
        {
            yellowLight.turnOFF();
            nextLight.turnON();
        }
        else if (timerTicks > 0)
        {
            timerTicks--;
        }
    }
    
    public void toggle()
    {
        if (greenLight.isON())
        {
            switchRed();
        }
        else if (redLight.isON())
        {
            switchGreen();
        }
    }
    
    public void switchGreen()
    {
        redLight.turnOFF();
        timerTicks = TRANSITION_TIME_TICKS;
        yellowLight.turnON();
        nextLight = greenLight;
    }
    
    public void switchRed()
    {
        greenLight.turnOFF();
        timerTicks = TRANSITION_TIME_TICKS;
        yellowLight.turnON();
        nextLight = redLight;
    }
}