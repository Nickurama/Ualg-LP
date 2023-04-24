class Light
{
    final private color OFFCOLOR = color(200, 200, 200);
    
    private boolean isON;
    private color drawColor;
    private float x;
    private float y;
    private float radius;
    
    public Light(float x, float y, float radius, color drawColor)
    {
        isON = false;
        this.x = x;
        this.y = y;
        this.radius = radius;
        this.drawColor = drawColor;
    }
    
    public void draw()
    {
        if (isON)
        {
            fill(drawColor);
        }
        else
        {
            fill(OFFCOLOR);
        }
        circle(x, y, radius * 2);
    }
    
    public void turnON() { isON = true; }
    public void turnOFF() { isON = false; }
    public boolean isON() { return isON; }
}