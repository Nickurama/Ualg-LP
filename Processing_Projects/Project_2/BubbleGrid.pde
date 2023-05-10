class BubbleGrid
{
    
    private float x;
    private float y;
    private int rows;
    private int columns;
    private int bubbleSize;
    private int padding;
    private int halfBubbleSize;
    private float cosThirty;
    private BubbleCell bubbleGrid[][];
    
    public BubbleGrid(float x, float y, int rows, int columns, int bubbleSize, int padding)
    {
        this.x = x;
        this.y = y;
        this.rows = rows;
        this.columns = columns;
        this.bubbleSize = bubbleSize;
        this.padding = padding;
        this.halfBubbleSize = bubbleSize / 2;
        this.cosThirty = cos(PI / 6);
        bubbleGrid = new BubbleCell[rows][columns];
        
        for (int i = 0; i < rows; i++)
        {
            bubbleGrid[i] = generateLine(i);
        }
    }
    
    private BubbleCell[] generateLine(int line)
    {
        BubbleCell bubbleLine[] = new BubbleCell[columns];
        
        float cellY = line * bubbleSize * cosThirty + halfBubbleSize + padding;
        
        if (line % 2 == 0)
        {
            for (int i = 0; i < columns; i++)
            {
                float cellX = i * bubbleSize + halfBubbleSize + padding;
                bubbleLine[i] = new BubbleCell(cellX, cellY, line, i);
            }
        }
        else
        {
            for (int i = 0; i < columns; i++)
            {
                float cellX = (i + 1) * bubbleSize + padding;
                bubbleLine[i] = new BubbleCell(cellX, cellY, line, i + 1);
            }
        }
        return bubbleLine;
    }
    
    public void snapCeiling(Bubble b)
    {
        if (rows > 0 && columns > 0)
        {
            float closestDist = b.dist(bubbleGrid[0][0].getX(), bubbleGrid[0][0].getY());
            BubbleCell closestCell = bubbleGrid[0][0]; //default
            
            for (BubbleCell cell : bubbleGrid[0]) //initial cell
            {
                if (!cell.hasBubble())
                {
                    closestCell = cell;
                    break;
                }
            }
            
            for (BubbleCell cell : bubbleGrid[0]) //closest cell
            {
                float newDist = b.dist(cell);
                if (newDist < closestDist && !cell.hasBubble())
                {
                    closestDist = newDist;
                    closestCell = cell;
                }
            }
            
            closestCell.setBubble(b);
            b.setCell(closestCell);
        }
    }
    
    private ArrayList<BubbleCell> getAdjacentCells(BubbleCell c)
    {
        ArrayList<BubbleCell> adjacentCells = new ArrayList<BubbleCell>();
        int row = c.getRow();
        int column = c.getColumn();
        
        if (row % 2 == 0) // even
        {
            if (column - 1 >= 0 && !bubbleGrid[row][column - 1].hasBubble) // left
            {
                println("found left: " + row + "," + (column - 1));
                adjacentCells.add(bubbleGrid[row][column - 1]);
            }
            if (column + 1 < columns && !bubbleGrid[row][column + 1].hasBubble) //right
            {
                println("found right: " + row + "," + (column + 1));
                adjacentCells.add(bubbleGrid[row][column + 1]);
            }
            
            if (row - 1 > 0) // up
            {
                int columnIndex = column - 1; // odds are shifted 1 to the left in the array
                if (column > 0 && !bubbleGrid[row - 1][columnIndex].hasBubble) // left (same column)
                {
                    println("found up left: " + (row - 1) + "," + column);
                    adjacentCells.add(bubbleGrid[row - 1][columnIndex]);
                }
                if (column < 9 && !bubbleGrid[row - 1][columnIndex + 1].hasBubble) // right
                {
                    println("found up right: " + (row - 1) + "," + (column + 1));
                    adjacentCells.add(bubbleGrid[row - 1][columnIndex + 1]);
                }
            }
            
            if (row + 1 < rows) // down
            {
                int columnIndex = column - 1; // odds are shifted 1 to the left in the array
                if (column > 0 && !bubbleGrid[row + 1][columnIndex].hasBubble) // left (same column)
                {
                    println("found down left: " + (row + 1) + "," + column);
                    adjacentCells.add(bubbleGrid[row + 1][columnIndex]);
                }
                if (column < 9 && !bubbleGrid[row + 1][columnIndex + 1].hasBubble) // right
                {
                    println("found down right: " + (row + 1) + "," + (column + 1));
                    adjacentCells.add(bubbleGrid[row + 1][columnIndex + 1]);
                }
            }
        }
        else // odd
        {
            int columnIndex = column - 1; // odds are shifted 1 to the left in the array
            if (column - 1 > 0 && !bubbleGrid[row][columnIndex - 1].hasBubble) // left
            {
                println("found left: " + row + "," + (column - 1));
                adjacentCells.add(bubbleGrid[row][columnIndex - 1]);
            }
            if (column + 1 < columns && !bubbleGrid[row][columnIndex + 1].hasBubble) //right
            {
                println("found right: " + row + "," + (column + 1));
                adjacentCells.add(bubbleGrid[row][columnIndex + 1]);
            }
            
            if (row - 1 >= 0) // up
            {
                if (!bubbleGrid[row - 1][column - 1].hasBubble) // left
                {
                    println("found up left: " + (row - 1) + "," + (column - 1));
                    adjacentCells.add(bubbleGrid[row - 1][column - 1]);
                }
                if (!bubbleGrid[row - 1][column].hasBubble) // right (same column)
                {
                    println("found up right: " + (row - 1) + "," + column);
                    adjacentCells.add(bubbleGrid[row - 1][column]);
                }
            }
            
            if (row + 1 <= rows) // down
            {
                if (!bubbleGrid[row + 1][column - 1].hasBubble) // left
                {
                    println("found down left: " + (row + 1) + "," + (column - 1));
                    adjacentCells.add(bubbleGrid[row + 1][column - 1]);
                }
                if (!bubbleGrid[row + 1][column].hasBubble) // right (same column)
                {
                    println("found down right: " + (row + 1) + "," + column);
                    adjacentCells.add(bubbleGrid[row + 1][column]);
                }
            }
        }
        
        return adjacentCells;
    }
    
    public void snap(Bubble snapBubble, Bubble anchor)
    {
        ArrayList<BubbleCell> adjacentCells = getAdjacentCells(anchor.getCell());
        
        if (adjacentCells.size() > 0)
        {
            float closestDist = snapBubble.dist(adjacentCells.get(0));
            BubbleCell closestCell = adjacentCells.get(0);
            
            for (BubbleCell cell : adjacentCells)
            {
                float newDist = snapBubble.dist(cell);
                if (newDist < closestDist)
                {
                    closestDist = newDist;
                    closestCell = cell;
                }
            }
            
            closestCell.setBubble(snapBubble);
            snapBubble.setCell(closestCell);
        }
        else
        {
            println("Error: no available adjacent cell!");
        }
    }
    
    private void drawDebug()
    {
        for (int i = 0; i < rows; i++)
        {
            int effectiveColumns = columns;
            if (i % 2 == 1)
            {
                effectiveColumns -= 1;
            }
            for (int j = 0; j < effectiveColumns; j++)
            {
                bubbleGrid[i][j].debugDraw();
            }
        }
    }
}