using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

static class constants
{
    public const uint minTime = 5;
    public const uint maxTime = 30;
    public const uint minQuestions = 1;
    public const uint minUsers = 1;
}

struct createRoomInformation
{
    public string roomName;
    public int numOfPlayers;
    public int numOfQuestions;
    public int timeForQuestion;
}

namespace Client
{
    /// <summary>
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Window
    {
        public const int createRoomSuccess = 502;
        private MainWindow mainWindow;
        public CreateRoom(MainWindow mainWindow)
        {
            InitializeComponent();
            this.mainWindow = mainWindow;
        }
        private void ButtonQuit(object sender, RoutedEventArgs e)
        {
            Close();
            mainWindow.Visibility = Visibility.Visible;
        }
        private void ButtonCreateRoom(object sender, RoutedEventArgs e)
        {
            CreateRoomRequest request = CreateRoomInfo();
            if (request.roomName == "")
            {
                return;
            }
            string json = Helper.CreateRoomToJson(request);
            Connector.SendMessage(Helper.BuildMessage(messageConstants.createRoom, json));
            string jsonAnswer = Connector.GetMessage();
            CreateRoomResponse responseCreateRoom = Helper.JsonToCreateRoom(jsonAnswer);
            if (responseCreateRoom.status == createRoomSuccess)
            {
                this.Visibility = Visibility.Hidden;
                User.adminOrNot = true;
                ShowPlayers showPlayersWindow = new ShowPlayers(this.mainWindow, responseCreateRoom.roomId);
                showPlayersWindow.WindowStartupLocation = WindowStartupLocation.CenterScreen;
                showPlayersWindow.Show();
            }
            else
            {
                Close();//just for now
            }
        }
               
        private CreateRoomRequest CreateRoomInfo()
        {
            CreateRoomRequest request;
            issueWithCreateRoom.Text = "";
            bool error = false;
            uint result;
            request.roomName = roomNameBox.Text;
            request.maxUsers = 0;
            request.questionCount = 0;
            request.answerTimeout = 0;
            if (uint.TryParse(NumOfPlayersBox.Text, out result))
            {
                if(result > 0)
                {
                    request.maxUsers = uint.Parse(NumOfPlayersBox.Text);
                }
            }
            if (uint.TryParse(NumOfQuestionsBox.Text, out result))
            {
                if (result > 0)
                {
                    request.questionCount = uint.Parse(NumOfQuestionsBox.Text);
                }
            }
            if (uint.TryParse(TimeForQuestionBox.Text, out result))
            {
                if (result > 0)
                {
                    request.answerTimeout = uint.Parse(TimeForQuestionBox.Text);
                }
            }
            if(request.roomName == "")
            {
                issueWithCreateRoom.Text += "The Name Of The Room Can't Be Empty\n";
                error = true;
            }
            if(request.answerTimeout < constants.minTime || request.answerTimeout > constants.maxTime)
            {
                issueWithCreateRoom.Text += "The Time For Each Question Must Be Between 5 To 30\n";
                error = true;
            }
            if(request.questionCount < constants.minQuestions || request.questionCount > 70)
            {
                issueWithCreateRoom.Text += "The Number Of Questions Must Be At least 1 and below 70\n";
                error = true;
            }
            if (request.maxUsers < constants.minUsers)
            {
                issueWithCreateRoom.Text += "The Number Of Players Must Be At least 1\n";
                error = true;
            }
            if(error == true)
            {
                request.roomName = "";
                issueWithCreateRoom.Visibility = Visibility.Visible;
            }
            else
            {
                issueWithCreateRoom.Visibility = Visibility.Hidden;
            }
            return request;
        }
        
    }
}
