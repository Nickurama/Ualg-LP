class Bubble
{
    //Bubble colors
    final private color ORANGE = color(255, 128, 0);
    final private color GREEN = color(51, 255, 51);
    final private color RED = color(255, 51, 51);
    final private color BLUE = color(0, 0, 255);
    final private color PINK = color(255, 204, 204);
    final private color YELLOW = color(255, 255, 51);
    
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
        this.cell = null;
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
    
    public color getColor() { return this.drawColor; }
    public void setCell(BubbleCell c) { this.cell = c; }
    public BubbleCell getCell() { return this.cell; }
    public void setPos(float x, float y) { setX(x); setY(y); }
    public void setX(float x) { this.x = x; }
    public float getX() { return this.x; }
    public void setY(float y) { this.y = y; }
    public float getY() { return this.y; }
}