class Bubble
{
    //fields
    final private int DEFAULT_SPEED = 1500;
    
    private float x;
    private float y;
    private int size;
    private float angle;
    private float speed;
    private color drawColor;
    private boolean isMoving;
    private boolean hasCollision;
    
    private BubbleCell cell;
    
    public Bubble(float x, float y, int size, color drawColor)
    {
        this.x = x;
        this.y = y;
        this.size = size;
        this.angle = 0;
        this.drawColor = drawColor;
        this.speed = DEFAULT_SPEED;
        this.isMoving = false;
        this.cell = null;
        this.hasCollision = false;
    }
    
    private void move(float deltaT)
    {
        if (isMoving)
        {
            x += deltaT * speed * cos(angle);
            y += deltaT * speed * sin(angle);
        }
    }
    
    public void launch(float angle)
    {
        this.angle = angle;
        isMoving = true;
    }
    
    public void launch()
    {
        isMoving = true;
    }
    
    public void stop()
    {
        isMoving = false;
    }
    
    public float dist(float x, float y)
    {
        return sqrt(pow((x - this.x), 2) + pow((y - this.y), 2));
    }
    
    public float dist(Bubble b)
    {
        return dist(b.getX(), b.getY());
    }
    
    public float dist(BubbleCell c)
    {
        return dist(c.getX(), c.getY());
    }
    
    private void ricochet()
    {
        angle = PI - angle;
    }
    
    public boolean collides(Bubble b, float collisionOffset)
    {
        return dist(b) < (float)size * collisionOffset;
    }
    
    public boolean collidesCeiling(float ceilingHeight)
    {
        boolean result = false;
        if (this.y - (float)this.size / 2 < ceilingHeight)
        {
            result = true;
            this.y = ceilingHeight + this.size / 2;
        }
        return result;
    }
    
    public boolean isBelowScreen(int windowHeight)
    {
        boolean result = false;
        if (this.y - this.size / 2 > windowHeight)
            result = true;
        return result;
    }
    
    public void handleWallCollision(int padding, int windowWidth)
    {
        if (this.x - this.size / 2 < padding)
        {
            this.x = padding + size / 2;
            ricochet();
        }
        else if (x + size / 2 > windowWidth - padding)
        {
            x = windowWidth - padding - this.size / 2;
            ricochet();
        }
    }
    
    public void update(float deltaT)
    {
        move(deltaT);
    }
    
    public void draw()
    {
        fill(drawColor);
        stroke(BLACK);
        strokeWeight(size / 10);
        circle(x, y, size);
    }
    
    public boolean isMoving() { return this.isMoving; }
    public void setCollision(boolean collision) { this.hasCollision = collision; }
    public boolean hasCollision() { return this.hasCollision; }
    public void setSpeed(float speed) { this.speed = speed; }
    public float getSpeed() { return this.speed; }
    public void setAngle(float angle) { this.angle = angle; }
    public float getAngle() { return this.angle; }
    public color getColor() { return this.drawColor; }
    public void setCell(BubbleCell c) { this.cell = c; }
    public BubbleCell getCell() { return this.cell; }
    public void setPos(float x, float y) { setX(x); setY(y); }
    public void setX(float x) { this.x = x; }
    public float getX() { return this.x; }
    public void setY(float y) { this.y = y; }
    public float getY() { return this.y; }
}