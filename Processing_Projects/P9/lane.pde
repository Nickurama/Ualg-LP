class Lane
{
    final private color DARK_GREY = color(64, 64, 64);
    final private color BLACK = color(0, 0, 0);
    
    final private float CAR_MAX_SPEED = 6;
    final private float CAR_MIN_SPEED = 2;
    final private float CAR_ACCEL = 0.025;
    
    private float x;
    private float y;
    private float width;
    private float length;
    private float rotationAngle;
    
    private Car car;
    private TrafficLight trafficLight;
    
    public Lane(float x, float y, float length, float rotationAngle)
    {
        this.x = x;
        this.y = y;
        this.length = length;
        this.width = length / 16;
        this.rotationAngle = -rotationAngle;
        car = spawnRandomCar();
        trafficLight = new TrafficLight( -(length / 6), width , width / 2, 0);
    }
    
    private Car spawnRandomCar()
    {
        int randomR = int(random(256));
        int randomG = int(random(256));
        int randomB = int(random(256));
        color randomColor = color(randomR, randomG, randomB);
        float randomMaxSpeed = random(CAR_MIN_SPEED, CAR_MAX_SPEED);
        return new Car( -(length / 2), 0, length / 16, 0, randomColor, randomMaxSpeed, randomMaxSpeed, CAR_ACCEL);
    }
    
    private void update()
    {
        //check if car reached end
        if (car.getX() > length / 2)
        {
            car = spawnRandomCar();
        }
        
        //check if car has reached the traffic light
        if (car.getX() < trafficLight.getX() && car.getX() > trafficLight.getX() - car.getWidth())
        {
            if (trafficLight.isRed() || trafficLight.isYellow())
            {
                car.stopMoving();
            }
        }
        
        //check if light is green again
        if (isStalled() && trafficLight.isGreen())
        {
            car.startMoving();
        }
    }
    
    public void draw()
    {
        update();
        
        pushMatrix();
        translate(x, y);
        rotate(radians(rotationAngle));
        // drawLane();
        car.draw();
        trafficLight.draw();
        popMatrix();
    }
    
    public void toggleGreen()
    {
        trafficLight.switchGreen();
    }
    
    public void toggleRed()
    {
        trafficLight.switchRed();
    }
    
    public boolean isStalled()
    {
        boolean result = false;
        if (!car.isMoving())
        {
            result = true;
        }
        return result;
    }
    
    public float carPos() { return car.getX(); }
    public boolean isRed() { return trafficLight.isRed(); }
    public boolean isGreen() { return trafficLight.isGreen(); }
    
    // private void drawLane()
    // {
    //     rectMode(CENTER);
    //     fill(DARK_GREY);
    //     noStroke();
    //     rect(0, 0, length, width);
    //     stroke(BLACK);
// }
}