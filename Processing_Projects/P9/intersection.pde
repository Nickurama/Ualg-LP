class Intersection
{
    final private int COOLDOWN_TIME_TICKS = 300;
    
    final private color DARK_GREEN = color(0, 128, 0);
    final private color DARK_GREY = color(64, 64, 64);
    final private color BLACK = color(0, 0, 0);
    
    private Lane eastLane;
    private Lane westLane;
    private Lane northLane;
    private Lane southLane;
    
    private int windowWidth;
    private int windowHeight;
    
    private int cooldownTicks;
    
    public Intersection(int windowWidth, int windowHeight)
    {
        this.windowWidth = windowWidth;
        this.windowHeight = windowHeight;
        
        eastLane = new Lane(windowWidth / 2, windowHeight / 2 + windowHeight / 32, windowWidth, 0);
        westLane = new Lane(windowWidth / 2, windowHeight / 2 - windowHeight / 32, windowWidth, 180);
        northLane = new Lane(windowWidth / 2 + windowWidth / 32, windowHeight / 2, windowHeight, 90);
        southLane = new Lane(windowWidth / 2 - windowWidth / 32, windowHeight / 2, windowHeight, 270);
        
        cooldownTicks = 0;
    }
    
    private boolean hasPassedIntersection(float pos)
    {
        boolean result = false;
        if (pos > windowWidth / 16 || pos < - windowWidth / 16)
        {
            result = true;
        }
        return result;
    }
    
    private void update()
    {
        if ((eastLane.isStalled() || westLane.isStalled()) && hasPassedIntersection(northLane.carPos()) && hasPassedIntersection(southLane.carPos()))
        {
            if (cooldownTicks == 0)
            {
                cooldownTicks = COOLDOWN_TIME_TICKS;
                eastLane.toggleGreen();
                westLane.toggleGreen();
                northLane.toggleRed();
                southLane.toggleRed();
            }
        }
        else if ((northLane.isStalled() || southLane.isStalled()) && hasPassedIntersection(eastLane.carPos()) && hasPassedIntersection(westLane.carPos()))
        {
            if (cooldownTicks == 0)
            {
                cooldownTicks = COOLDOWN_TIME_TICKS;
                northLane.toggleGreen();
                southLane.toggleGreen();
                eastLane.toggleRed();
                westLane.toggleRed();
            }
        }
        
        if (cooldownTicks > 0)
        {
            cooldownTicks--;
        }
    }
    
    public void draw()
    {
        update();
        
        drawBackground();
        drawRoads();
        drawLanes();
    }
    
    private void drawBackground()
    {
        background(DARK_GREEN);
    }
    
    private void drawRoads()
    {
        rectMode(CENTER);
        fill(DARK_GREY);
        noStroke();
        rect(windowWidth / 2, windowHeight / 2, windowWidth / 8, windowHeight);
        rect(windowWidth / 2, windowHeight / 2, windowWidth, windowHeight / 8);
        stroke(BLACK);
    }
    
    private void drawLanes()
    {
        eastLane.draw();
        westLane.draw();
        northLane.draw();
        southLane.draw();
    }
}