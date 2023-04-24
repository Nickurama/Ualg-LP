class Intersection
{
    final private color DARK_GREEN = color(0, 128, 0);
    final private color DARK_GREY = color(64, 64, 64);
    final private color BLACK = color(0, 0, 0);
    
    private Lane eastLane;
    private Lane westLane;
    private Lane northLane;
    private Lane southLane;
    
    private int windowWidth;
    private int windowHeight;
    
    public Intersection(int windowWidth, int windowHeight)
    {
        this.windowWidth = windowWidth;
        this.windowHeight = windowHeight;
        
        eastLane = new Lane(windowWidth / 2, windowHeight / 2 + windowHeight / 32, windowWidth, 0);
        eastLane.toggleGreen();
        westLane = new Lane(windowWidth / 2, windowHeight / 2 - windowHeight / 32, windowWidth, 180);
        northLane = new Lane(windowWidth / 2 + windowWidth / 32, windowHeight / 2, windowWidth, 90);
        southLane = new Lane(windowWidth / 2 - windowWidth / 32, windowHeight / 2, windowWidth, 270);
    }
    
    private void update()
    {
        
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