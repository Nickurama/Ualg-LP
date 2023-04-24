class Car
{
    final private color BLACK = color(0, 0, 0);
    final private float ACCEL = 0.05;
    
    private float x;
    private float y;
    private float width;
    private float height;
    private float rotationAngle;
    private color drawColor;
    
    private float speed;
    private float maxSpeed;
    
    private boolean isMoving;
    
    public Car(float startingX, float startingY, float width, float rotationAngle, color drawColor, float startingSpeed, float maxSpeed)
    {
        this.x = startingX;
        this.y = startingY;
        this.width = width;
        this.height = width / 2;
        this.rotationAngle = -rotationAngle;
        this.drawColor = drawColor;
        
        this.speed = startingSpeed;
        this.maxSpeed = maxSpeed;
        
        isMoving = false;
    }
    
    public void toggleMovement()
    {
        if (isMoving)
        {
            stopMoving();
        }
        else
        {
            startMoving();
        }
    }
    
    public void startMoving()
    {
        isMoving = true;
    }
    
    public void stopMoving()
    {
        speed = 0;
        isMoving = false;
    }
    
    
    private void accelerate()
    {
        if (this.speed < maxSpeed)
        {
            this.speed = this.speed + ACCEL;
            if (this.speed > maxSpeed)
            {
                this.speed = maxSpeed;
            }
        }
    }
    
    private void move()
    {
        this.x = this.x + this.speed * cos(radians(rotationAngle));
        this.y = this.y + this.speed * sin(radians(rotationAngle));
        accelerate();
    }
    
    
    private void update()
    {
        if (isMoving)
        {
            move();
        }
    }
    
    public void draw()
    {
        update();
        pushMatrix();
        rectMode(CENTER);
        translate(x, y);
        rotate(radians(rotationAngle));
        drawWheels();
        drawBody();
        popMatrix();
    }
    
    private void drawBody()
    {
        fill(drawColor);
        rect( -(width * 0.4) / 2, 0, width * 0.6, height);
        rect((width * 0.6) / 2, 0,width * 0.4, height);
    }
    
    private void drawWheels()
    {
        fill(BLACK);
        rect( -(width / 2) + width / 6, -(height / 2), width / 4, height / 4);
        rect((width / 2) - width / 6, -(height / 2), width / 4, height / 4);
        rect( -(width / 2) + width / 6,(height / 2), width / 4, height / 4);
        rect((width / 2) - width / 6,(height / 2), width / 4, height / 4);
    }
}