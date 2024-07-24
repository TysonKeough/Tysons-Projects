using System;
class Program
{//Variables used
    static char[]? board;
    static char player;
    static char computer;
    static bool startup;
    static bool Continued;
    static bool End;
    static void Main(string[] args)
    {
        while (true)
        {//While true
            bool Continued = true; //Make Continued True
            bool End = true; //Make End True
            InitializeBoard();//Setup the Game board
            startup = true;//make startup true
            Console.WriteLine("Welcome to Tic Tac Toe!");//Greet the user 
            while (startup == true)//while startup is true
            {
                Console.WriteLine("Please Pick Either 'X' or 'O': ");//Ask user to pick between X and O
                player = char.ToUpper(Console.ReadKey().KeyChar);//Store the players choice

                if (player == 'X')//if player chooses X 
                {
                    computer = 'O';//make computer O
                    startup = false;//make startup false
                }
                else if (player == 'O')//else if Player is O
                {
                    computer = 'X';//make computer X
                    startup = false;//make startup false
                }
                else
                {
                    Console.WriteLine("Invalid Input Please Enter Either 'X' or 'O' ");//if user does not choose between X or O make them pick again
                    continue;
                }
            }
            int turnsplayed = 1;//Start turns Counter
            int choicemade;//make an integer to store what choice was made
            do
            {
                Console.Clear();//Clear the Console
                Console.WriteLine("Turn: " + turnsplayed);//Says what turn you are on
                Console.WriteLine("Player: " + player + " Computer: " + computer);//Says what the player and computer have chosen
                Console.WriteLine("Please Press Enter to Begin.");//asks user to press enter to begin the game
                Console.ReadLine();//waits till user presses enter to start game
                GameBoard();//prints game board

                // This is the Players and Computers Moves
                if (turnsplayed % 2 == 0)//if the number is even Computers turn
                {
                    Console.WriteLine("Computer's turn (" + computer + "):");//Say that its the computers turn
                    Console.WriteLine("Press Enter to End the Computers Turn");//Asks user to end the computers turn
                    Console.ReadLine();//waits till user ends the turn
                    choicemade = ComputersTurn();//store the computers choice
                }
                else
                {
                    Console.WriteLine("Your turn (" + player + "):");//Say that its the users turn 
                    Console.WriteLine("Please Select a spot on the board 1-9");//asks them to pick a spot on the board between 1-9
                    choicemade = int.Parse(Console.ReadLine());//stores user choice
                    if (choicemade > 9 || choicemade <= 0)//if the choice is not on the board
                    {
                        Console.WriteLine("Invalid input Please Try Again");//tell them to pick again
                        choicemade = int.Parse(Console.ReadLine());//store the users choice
                    }
                }

                // This is What makes the moves happen
                if (ValidMove(choicemade))//if move is valid
                {
                    board[choicemade - 1] = turnsplayed % 2 == 0 ? computer : player; //Change the board to match the choice made
                    turnsplayed++;//add one to turns played 
                }

            } while (!WinConditions() && !IsAdraw());

            // This is for when someone wins 
            Console.Clear();//clears console
            GameBoard();//prints the board
            if (WinConditions())// if the winconditions is tru
            {
                Console.WriteLine(turnsplayed % 2 == 0 ? "You win!" : "Computer wins!");//say who won the game 
            }
            else//else say its a draw
            {
                Console.WriteLine("It's a draw!");
            }
            while (Continued == true)//while continued is true
            {
                Console.Write("Do you want to play again? (Y/N): ");//ask user if they would like to play again
                string PlayAgain = Console.ReadLine();//wait for users response

                if (PlayAgain == ("Y"))//if they do 
                {
                    Continued = false;//make continued false

                }
                else if (PlayAgain == ("N"))//if not 
                {
                    End = false;//make end false
                    Continued = false;//make continued false
                    break;//break 
                }
                else
                { // else invalid input please try again
                    Console.WriteLine("Invalid input Try again");
                    continue;
                }
            }
            if (End == false)
            { // if they chose no say thanks for playing and wait till user ends program.
                Console.WriteLine("Thank you for playing please press enter to close the game.");
                Console.ReadLine();
                break;
            }
        }
    }
    static void InitializeBoard()//this sets up the game board with numbers from 1-9
    {
        board = new char[] { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    }
    static void GameBoard()//This how the game board is printed
    {
        Console.Clear();
        Console.WriteLine("     |     |    ");
        Console.WriteLine($"  {board[0]}  |  {board[1]}  |  {board[2]} ");
        Console.WriteLine("_____|_____|_____");
        Console.WriteLine("     |     |    ");
        Console.WriteLine($"  {board[3]}  |  {board[4]}  |  {board[5]} ");
        Console.WriteLine("_____|_____|_____");
        Console.WriteLine("     |     |    ");
        Console.WriteLine($"  {board[6]}  |  {board[7]}  |  {board[8]} ");
        Console.WriteLine("     |     |    ");
    }

    static bool WinConditions()//This checks all of the win conditions to see who wins
    {
        for (int i = 0; i < 3; i++)
        {
            if ((board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2]) || //checks the board and if its true
                         (board[i] == board[i + 3] && board[i + 3] == board[i + 6]))
            {
                return true;//return the value true
            }
        }
        if ((board[0] == board[4] && board[4] == board[8]) ||//check another win condition
                    (board[2] == board[4] && board[4] == board[6]))
        {
            return true;//return true if its correct
        }
        return false;//else return false
    }

    static bool IsAdraw()//Check if its a draw
    {
        foreach (char c in board)//checks the board to see if there is no win
        {
            if (c != 'X' && c != 'O')
                return false;// if so return false
        }
        return true;//else return true
    }

    static bool ValidMove(int choice)// this is what checks to see if a move is valid
    {
        return board[choice - 1] != 'X' && board[choice - 1] != 'O';
    }

    static int ComputersTurn()// This is how the computer makes his move
    {
        // Used the minimax algorithm to find the best move available on the board
        int bestMove = -1;
        int bestScore = int.MinValue;

        for (int i = 0; i < 9; i++)//goes 9 times to check each spot on the board
        {
            if (board[i] != 'X' && board[i] != 'O')//checks if the spot is full or not
            {
                char temp = board[i];
                board[i] = computer;
                int score = Minimax(board, 0, false);
                board[i] = temp;

                if (score > bestScore) 
                {
                    bestScore = score;
                    bestMove = i + 1;
                }
            }
        }

        return bestMove;//returns the best move available 
    }

    static int Minimax(char[] board, int depth, bool isMaximizing)//This is the Minimax Algorithm
    {
        if (WinConditions())// check the win conditions 
        {
            return isMaximizing ? -1 : 1;  
        }

        if (IsAdraw())// check if its a draw
        {
            return 0; //return 0
        }
        int score;//declare new variable
        if (isMaximizing)//if it can block a play or win
        {
            score = int.MinValue;
            for (int i = 0; i < 9; i++)//check the board for a min value
            {
                if (board[i] != 'X' && board[i] != 'O')
                {
                    char temp = board[i];
                    board[i] = computer;
                    score = Math.Max(score, Minimax(board, depth + 1, !isMaximizing));
                    board[i] = temp;
                }
            }
        }
        else
        {
            score = int.MaxValue;
            for (int i = 0; i < 9; i++)//check the board for a max value
            {
                if (board[i] != 'X' && board[i] != 'O')
                {
                    char temp = board[i];
                    board[i] = player;
                    score = Math.Min(score, Minimax(board, depth + 1, !isMaximizing));
                    board[i] = temp;
                }
            }
        }

        return score;//returns the score
    }

}

