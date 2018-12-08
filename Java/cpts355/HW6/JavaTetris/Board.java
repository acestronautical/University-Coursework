import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
//import java.io.Console; //Enable this if you would like to print on the console for debugging
import java.util.HashSet;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.Timer;

public class Board extends JPanel implements ActionListener {
    /* define constants for customizing the game */
    public final int BOARD_WIDTH = 10; // number of rows in the board
    public final int BOARD_HEIGHT = 20; // number of columns
    public final int CELL_WIDTH = 30;
    public final int CELL_HEIGHT = 35;
    public final char SPACE = ' ';
    public final String TARGET = "355";

    private final int DELAY = 400;
    private static final Color BLACK = new Color(0, 0, 0);

    private Timer timer; // We use the java.util.Timer to create a game cycle. The shapes move on a
                         // square by square basis (not pixel by pixel).
    private boolean isFallingFinished = false; // isFallingFinished is set to true when the fall of a piece is
                                               // completed; it is set to false when the next piece starts to fall.
    private boolean isStarted = false; // isStarted is set to false when the board height reaches the limit and the
                                       // next piece can't be moved (i.e., game is over). The program exist when
                                       // isStarted becomes false.
    private boolean isPaused = false; // set to true when the game is paused; false otherwise.
    private JLabel statusbar;
    private JLabel scorebar; // The label displaying the game score
    private JLabel scoretext;
    private Font textFont;
    private Piece curPiece; // The current (falling) piece
    private char[][] board; // The board grid
    private Player player = new Player(0, 0);

    public class Player {

        private int points;
        private int cleared;

        Player(int p, int c) {
            points = p;
            cleared = c;
        }

        public int getPoints() {
            return points;
        }

        public int getCleared() {
            return cleared;
        }

        public void setPoints(int p) {
            points = p;
            scorebar.setText(Integer.toString(points));
        }

        public void setCleared(int c) {
            cleared = c;
            statusbar.setText(Integer.toString(cleared));
        }

    }

    public Board(Tetris parent) {

        initBoard(parent);
    }

    /*
     * clear all cells on the board. A cell in the board is considered empty if the
     * character at that cell is SPACE. Iniatially all cells are initialized with
     * SPACE.
     */
    private void clearBoard() {
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                board[j][i] = SPACE;
            }
        }
    }

    /* calculate the cell width and height in pixels */
    private int squareWidth() {
        return (int) getSize().getWidth() / BOARD_WIDTH;
    }

    private int squareHeight() {
        return (int) getSize().getHeight() / BOARD_HEIGHT;
    }

    /*
     * calculate the X coordinate of the left upper corner of j th cell on a row. (j
     * is a 0-based index)
     */
    private int calcX(int j) {
        return (j * squareWidth());

    }

    /*
     * calculate the Y coordinate of the left upper corner of i th cell on a column.
     * (i is a 0-based index)
     */
    private int calcY(int i) {
        Dimension size = getSize();
        int boardTop = (int) size.getHeight() - BOARD_HEIGHT * squareHeight();
        return (boardTop + i * squareHeight());

    }

    /* initialize the game board, create the first piece, and start the timer */
    private void initBoard(Tetris parent) {

        setFocusable(true);
        curPiece = new Piece();
        // create the Timer. The board object is registered as the listener for the
        // timer. When the timer is fired, Board's action listener method will be
        // called.
        timer = new Timer(DELAY, this);
        timer.start();

        this.textFont = new Font("Helvatica", Font.BOLD, 22);
        statusbar = parent.getStatusBar(); // get the reference to the Tetris's status bar
        scorebar = parent.getScoreBar(); // get the reference to the Tetris's score bar
        scoretext = parent.getScoreText(); // get the reference to the Tetris's score bar

        scoretext.setFont(textFont);
        scorebar.setBorder(BorderFactory.createEtchedBorder(1));
        scorebar.setFont(textFont);
        statusbar.setFont(textFont);

        addKeyListener(new TAdapter());
        // create and clear the board
        board = new char[BOARD_WIDTH][BOARD_HEIGHT];
        clearBoard();

    }

    /* When Timer is fired, Board's override of actionPerformed will be called */
    @Override
    public void actionPerformed(ActionEvent e) {
        /* if the falling of the current piece is completed, create a new piece */
        if (isFallingFinished) {
            isFallingFinished = false;
            createNewPiece();
        } else { // else move the current piece one level down on the board.
            oneLineDown();
        }
    }

    /* Start the game. */
    public void start() {

        if (isPaused)
            return;

        isStarted = true;
        isFallingFinished = false;

        createNewPiece();
        timer.start();
        clearBoard();
    }

    /* Pause the game. */
    private void pause() {

        if (!isStarted)
            return;

        isPaused = !isPaused;

        if (isPaused) {

            timer.stop();
            statusbar.setText("PAUSED");
        } else {

            timer.start();
            statusbar.setText(" ");
        }

        repaint();
    }

    /*
     * draw a square over the non-empty board cells (a cell is non-empty if its
     * value is not SPACE). The color of the cell is determined based on the cell
     * value.
     */
    private void drawSquare(Graphics g, int x, int y, char number) {

        Color colors[] = { new Color(50, 150, 50), new Color(204, 102, 102), new Color(102, 204, 102),
                new Color(102, 102, 204), new Color(204, 204, 102), new Color(204, 102, 204), new Color(0, 255, 0),
                new Color(0, 0, 255), new Color(102, 204, 204), new Color(218, 170, 0) };

        Color color = colors[Character.getNumericValue(number)];

        g.setColor(color);
        g.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2);
        g.setColor(BLACK);
        g.setFont(textFont);
        g.drawString(String.valueOf(number), x + (squareWidth() - (CELL_WIDTH / 2) + 1) / 2,
                y + (squareHeight() + (CELL_HEIGHT / 2)) / 2);

        g.setColor(color.brighter());
        g.drawLine(x, y + squareHeight() - 1, x, y);
        g.drawLine(x, y, x + squareWidth() - 1, y);

        g.setColor(color.darker());
        g.drawLine(x + 1, y + squareHeight() - 1, x + squareWidth() - 1, y + squareHeight() - 1);
        g.drawLine(x + squareWidth() - 1, y + squareHeight() - 1, x + squareWidth() - 1, y + 1);

    }

    /*
     * draw the squares for the non empty cells on the board (already dropped pieces
     * and the current piece currently falling)
     */
    private void doDrawing(Graphics g) {

        /* draw the squares for already dropped pieces */
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                if (board[j][i] != SPACE) {
                    drawSquare(g, calcX(j), calcY(i), board[j][i]);
                }
            }
        }
        /* draw the square for the currently dropping piece */
        if (curPiece.getNumber() != SPACE) {
            drawSquare(g, calcX(curPiece.getX()), calcY(curPiece.getY()), curPiece.getNumber());

        }
    }

    /*
     * Board's overwrite for paintComponent. This will be called every time
     * "repaint() is called .
     */
    @Override
    public void paintComponent(Graphics g) {

        super.paintComponent(g);
        doDrawing(g);
    }

    /* move the current piece all the way down on the board */
    private void dropDown() {

        int newY = curPiece.getY();

        while (newY < BOARD_HEIGHT - 1) {

            if (!tryMove(curPiece, 0, 1))
                break;
            ++newY;
        }

        pieceDropped();
    }

    /* move the current piece one row down on the board */
    private void oneLineDown() {

        if (!tryMove(curPiece, 0, 1))
            pieceDropped();
    }

    /*
     * checks if the fall of the current piece is completed. **TODO** If so, updates
     * the board and the score.
     */
    private void pieceDropped() {
        updateBoard(curPiece);

        if (!isFallingFinished)
            createNewPiece();
    }

    /*
     * creates the new piece; if the board is full (i.e, can't move the current
     * piece) stops the game.
     */
    private void createNewPiece() {

        curPiece.setRandomNumber();
        curPiece.setX(BOARD_WIDTH / 2 + 1);
        curPiece.setY(0);

        if (!tryMove(curPiece, 0, 0)) {

            curPiece.setNumber(SPACE);
            timer.stop();
            isStarted = false;
            statusbar.setText("GAME OVER");
        }
    }

    /* moves the current piece by newX,newY on the Board and repaints the Board */
    private boolean tryMove(Piece newPiece, int newX, int newY) {
        int x = newPiece.getX() + newX;
        int y = newPiece.getY() + newY;

        if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT)
            return false;

        if (board[x][y] != SPACE)
            return false;

        curPiece = newPiece;
        curPiece.setX(x);
        curPiece.setY(y);

        repaint();

        return true;
    }

    /*
     * Updates the Board: clears all cell groups including 3 (or more) matching
     * adjacent cells clears all cell groups including the target characters - can
     * appear either horizontal(left to right or right to left ) or vertical (up to
     * down or down to up) - the characters of the target string need to appear in
     * the same order.
     */
    public void updateBoard(Piece curPiece) {

        board[curPiece.getX()][curPiece.getY()] = curPiece.getNumber();

        boolean lookingForMatches = true;
        MatchHunter matchHunter = new MatchHunter();
        HashSet<coordinate> newMatches;
        while (lookingForMatches) {
            lookingForMatches = false;
            // find matches
            newMatches = matchHunter.hunt();
            if (!newMatches.isEmpty()) {
                lookingForMatches = true;
            }
            // for each match
            for (coordinate c : newMatches) {
                // delete space <- not needed
                board[c.X][c.Y] = SPACE;
                // apply gravity
                 for (int i = c.Y; i > 0; i--) {
                 board[c.X][i] = board[c.X][i - 1];
                 }
                 board[c.X][0] = SPACE;
                // increase player points
                player.setPoints(player.getPoints() + 5);
                player.setCleared(player.getCleared() + 1);

            }
            matchHunter.clearMatches();
        }
    }

    public class coordinate {
        int X;
        int Y;

        public boolean equals(Object o) {
            coordinate c = (coordinate) o;
            return c.X == X && c.Y == Y;
        }

        public coordinate(int x, int y) {
            this.X = x;
            this.Y = y;
        }

        public int hashCode() {
            return Integer.parseInt(X + "0" + Y);
        }
    }

    public class MatchHunter {

        HashSet<coordinate> matches = new HashSet<coordinate>();

        public void clearMatches() {
            matches = new HashSet<coordinate>();
        }

        public HashSet<coordinate> hunt() {
            HashSet<coordinate> found;
            // For every position on board
            // board from bottom to top
            for (int i = 0; i < BOARD_HEIGHT; i++) {
                for (int j = 0; j < BOARD_WIDTH; j++) {
                    if (board[j][i] != SPACE) {
                        found = huntHelper(new coordinate(j, i), "", new HashSet<coordinate>());
                        matches.addAll(found);
                    }
                }
            }
            return matches;
        }

        private HashSet<coordinate> huntHelper(coordinate cur, String sequence, HashSet<coordinate> visited) {
            // Return empty set if outside board or on empty position or seen before
            if (cur.X >= BOARD_WIDTH || cur.X < 0)
                return new HashSet<coordinate>();
            if (cur.Y >= BOARD_HEIGHT || cur.Y < 0)
                return new HashSet<coordinate>();
            if (board[cur.X][cur.Y] == SPACE)
                return new HashSet<coordinate>();
            if (visited.contains(cur))
                return new HashSet<coordinate>();

            // Add current character to current sequence
            sequence += board[cur.X][cur.Y];
            // Add current coordinate to visited coordinates
            visited.add(cur);
            // Create pattern
            String pattern = "((?:([0-9])\\2\\2)|(" + TARGET + "))";
            // Create regex
            Pattern r = Pattern.compile(pattern);
            // Create matcher
            Matcher m = r.matcher(sequence);

            // Check for matches
            if (m.find()) {
                if (!m.group(2).isEmpty()) 
                    player.setPoints(player.getPoints() + 5);
                return visited;
            } else if (sequence.length() < 3) {
                HashSet<coordinate> union = new HashSet<coordinate>();
                union.addAll(huntHelper(new coordinate(cur.X + 1, cur.Y), sequence, new HashSet<coordinate>(visited)));
                union.addAll(huntHelper(new coordinate(cur.X - 1, cur.Y), sequence, new HashSet<coordinate>(visited)));
                union.addAll(huntHelper(new coordinate(cur.X, cur.Y + 1), sequence, new HashSet<coordinate>(visited)));
                union.addAll(huntHelper(new coordinate(cur.X, cur.Y - 1), sequence, new HashSet<coordinate>(visited)));
                return union;
            } else {
                return new HashSet<coordinate>();
            }
        }

    }

    /* handles the key presses */
    class TAdapter extends KeyAdapter {

        @Override
        public void keyPressed(KeyEvent e) {

            if (!isStarted || curPiece.getNumber() == SPACE) {
                return;
            }

            int keycode = e.getKeyCode();

            if (keycode == 'P') {
                pause();
                return;
            }

            if (isPaused)
                return;

            switch (keycode) {

            case KeyEvent.VK_LEFT:
                tryMove(curPiece, -1, 0);
                break;

            case KeyEvent.VK_RIGHT:
                tryMove(curPiece, 1, 0);
                break;

            case KeyEvent.VK_DOWN:
                tryMove(curPiece, 0, 2);
                break;

            case KeyEvent.VK_UP:
                tryMove(curPiece, 0, 0);
                break;

            case KeyEvent.VK_SPACE:
                dropDown();
                break;

            case 'D':
                oneLineDown();
                break;
            }
        }
    }
}
