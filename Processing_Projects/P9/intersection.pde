class Intersection
{
    final private int COOLDOWN_TIME_TICKS = 180;
    final private int ALL_RED_TIME = 120;
    
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
    private int allRedTime;
    private boolean isNS;
    
    public Intersection(int windowWidth, int windowHeight)
    {
        this.windowWidth = windowWidth;
        this.windowHeight = windowHeight;
        
        eastLane = new Lane(windowWidth / 2, windowHeight / 2 + windowHeight / 32, windowWidth, 0);
        westLane = new Lane(windowWidth / 2, windowHeight / 2 - windowHeight / 32, windowWidth, 180);
        northLane = new Lane(windowWidth / 2 + windowWidth / 32, windowHeight / 2, windowHeight, 90);
        southLane = new Lane(windowWidth / 2 - windowWidth / 32, windowHeight / 2, windowHeight, 270);
        
        cooldownTicks = COOLDOWN_TIME_TICKS;
        allRedTime = ALL_RED_TIME;
        isNS = true;
        turnAllRed();
        northLane.toggleGreen();
        southLane.toggleGreen();
    }
    
    private boolean isCarInIntersection(float carPos, float trafficLightPos)
    {
        boolean result = true;
        if (carPos < trafficLightPos || carPos > - trafficLightPos)
        {
            result = false;
        }
        return result;
    }
    
    private void turnAllRed()
    {
        northLane.toggleRed();
        southLane.toggleRed();
        eastLane.toggleRed();
        westLane.toggleRed();
    }
    
    private void switchNS()
    {
        cooldownTicks = COOLDOWN_TIME_TICKS;
        allRedTime = ALL_RED_TIME;
        northLane.toggleGreen();
        southLane.toggleGreen();
        isNS = true;
    }
    
    private void switchEW()
    {
        cooldownTicks = COOLDOWN_TIME_TICKS;
        allRedTime = ALL_RED_TIME;
        eastLane.toggleGreen();
        westLane.toggleGreen();
        isNS = false;
    }
    
    private void switchLanes()
    {
        turnAllRed();
        if (allRedTime == 0)
        {
            if (isNS)
            {
                if (!isCarInIntersection(northLane.carPos(), northLane.trafficLightPos()) && 
                    !isCarInIntersection(southLane.carPos(), southLane.trafficLightPos()) && 
                    northLane.isRed() && southLane.isRed())
                {
                    switchEW();
                }
            }
            else if (!isNS)
            {
                if (!isCarInIntersection(eastLane.carPos(), eastLane.trafficLightPos()) && 
                    !isCarInIntersection(westLane.carPos(), westLane.trafficLightPos()) && 
                    eastLane.isRed() && westLane.isRed())
                {
                    switchNS();
                }
            }
        }
        else if (allRedTime > 0)
        {
            allRedTime--;
        }
    }
    
    private void update()
    {
        if (cooldownTicks == 0)
            {
            switchLanes();
        }
        else if (cooldownTicks > 0)
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