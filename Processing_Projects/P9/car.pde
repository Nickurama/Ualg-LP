class Car
{
    final private color BLACK = color(0, 0, 0);
    
    private float x;
    private float y;
    private float width;
    private float height;
    private float rotationAngle;
    private color drawColor;
    
    private float speed;
    private float maxSpeed;
    private float acceleration;
    
    private boolean isMoving;
    
    public Car(float startingX, float startingY, float width, float rotationAngle, color drawColor, float startingSpeed, float maxSpeed, float acceleration)
    {
        this.x = startingX;
        this.y = startingY;
        this.width = width;
        this.height = width / 2;
        this.rotationAngle = -rotationAngle;
        this.drawColor = drawColor;
        
        this.speed = startingSpeed;
        this.maxSpeed = maxSpeed;
        this.acceleration = acceleration;
        
        isMoving = true;
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
            this.speed = this.speed + acceleration;
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
        rect( -(this.width * 0.4) / 2, 0, this.width * 0.6, this.height);
        rect((this.width * 0.6) / 2, 0, this.width * 0.4, this.height);
    }
    
    private void drawWheels()
    {
        fill(BLACK);
        rect( -(this.width / 2) + this.width / 6, -(this.height / 2), this.width / 4, this.height / 4);
        rect((this.width / 2) - this.width / 6, -(this.height / 2), this.width / 4, this.height / 4);
        rect( -(this.width / 2) + this.width / 6,(this.height / 2), this.width / 4, this.height / 4);
        rect((this.width / 2) - this.width / 6,(this.height / 2), this.width / 4, this.height / 4);
    }
}