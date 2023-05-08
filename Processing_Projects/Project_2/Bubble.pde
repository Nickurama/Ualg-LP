class Bubble
{
    final private int DEFAULT_SPEED = 3;

    private int x;
    private int y;
    private int size;
    private float angle;
    private float speed;
    private color drawColor;
    private boolean isMoving;

    public Bubble(int x, int y, int size, float angle, color drawColor)
    {
        this.x = x;
        this.y = y;
        this.size = size;
        this.angle = angle - PI/2;
        this.drawColor = drawColor;
        this.speed = DEFAULT_SPEED;
        this.isMoving = false;
    }

    private void move()
    {
        if (isMoving)
        {
            x += speed * cos(angle);
            y += speed * sin(angle);
        }
    }

    public void Launch(float angle)
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
}