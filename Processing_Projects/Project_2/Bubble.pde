class Bubble
{

    //Bubble colors
    final private color ORANGE = color(248, 184, 139);
    final private color GREEN = color(186, 237, 145);
    final private color RED = color(254, 163, 170);
    final private color BLUE = color(178, 206, 254);
    final private color PINK = color(255, 192, 203);
    final private color PURPLE = color(128, 0, 128);

    final private int COLOR_AMMOUNT = 6;
    final private color[] COLORS = { ORANGE, GREEN, RED, BLUE, PINK, PURPLE };

    //fields
    final private int DEFAULT_SPEED = 15;

    private int x;
    private int y;
    private int size;
    private float angle;
    private float speed;
    private color drawColor;
    private boolean isMoving;

    public Bubble(int x, int y, int size, color drawColor)
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

    public void setPos(int x, int y) { setX(x); setY(y); }
    public void setX(int x) { this.x = x; }
    public void setY(int y) { this.y = y; }
}