class Bubble
{
    
    //Bubble colors
    final private color ORANGE = color(255, 233, 186);
    final private color GREEN = color(186, 255, 201);
    final private color RED = color(255, 179, 186);
    final private color BLUE = color(186, 225, 255);
    final private color PINK = color(255, 192, 203);
    final private color YELLOW = color(255, 255, 186);
    
    final private int COLOR_AMMOUNT = 6;
    final private color[] COLORS = { ORANGE, GREEN, RED, BLUE, PINK, YELLOW };
    
    //fields
    final private int DEFAULT_SPEED = 15;
    
    private float x;
    private float y;
    private int size;
    private float angle;
    private float speed;
    private color drawColor;
    private boolean isMoving;
    
    public Bubble(float x, float y, int size, color drawColor)
    {
        this.x = x;
        this.y = y;
        this.size = size;
        this.angle = 0;
        this.drawColor = drawColor;
        this.speed = DEFAULT_SPEED;
        this.isMoving = false;
    }
    
    public Bubble(int x, int y, int size)
    {
        this.x = x;
        this.y = y;
        this.size = size;
        this.angle = 0;
        this.drawColor = randomColor();
        this.speed = DEFAULT_SPEED;
        this.isMoving = false;
    }
    
    private color randomColor()
    {
        return COLORS[int(random(COLOR_AMMOUNT))];
    }
    
    private void move()
    {
        if (isMoving)
        {
            x += speed * cos(angle);
            y += speed * sin(angle);
        }
    }
    
    public void ricochet()
    {
        angle = PI - angle;
    }
    
    public void launch(float angle)
    {
        this.angle = angle;
        isMoving = true;
    }
    
    public void update()
    {
        move();
    }
    
    public void draw()
    {
        fill(drawColor);
        stroke(BLACK);
        strokeWeight(size / 10);
        circle(x, y, size);
    }
    
    public void setPos(float x, float y) { setX(x); setY(y); }
    public void setX(float x) { this.x = x; }
    public float getX() { return this.x; }
    public void setY(float y) { this.y = y; }
    public float getY() { return this.y; }
}