class Lane
{
    final private float CAR_MAX_SPEED = 5;
    final private float CAR_ACCEL = 0.025;
    final private float CAR_WIDTH = 100;
    
    
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
        float randomMaxSpeed = random(1, 8);
        return new Car( -(length / 2), 0, CAR_WIDTH, 0, randomColor, randomMaxSpeed, randomMaxSpeed, CAR_ACCEL);
    }
    
    private void update()
    {
        
    }
    
    public void draw()
    {
        update();
        
        pushMatrix();
        translate(x, y);
        rotate(radians(rotationAngle));
        drawLane();
        car.draw();
        trafficLight.draw();
        popMatrix();
    }
    
    private void drawLane()
    {
        rectMode(CENTER);
        rect(0, 0, length, width);
    }
}