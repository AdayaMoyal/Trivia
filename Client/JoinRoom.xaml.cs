using Microsoft.VisualBasic;
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
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Threading;


namespace Client
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        private MainWindow mainWindow;
        private GetRoomsResponse roomsResponse;
        private DispatcherTimer threadTimer;
        public JoinRoom(MainWindow mainWindow)
        {
            User.adminOrNot = false;
            InitializeComponent();
            this.mainWindow = mainWindow;
            threadTimer = new DispatcherTimer();
            threadTimer.Tick += ButtonJoinRoom;
            threadTimer.Interval = TimeSpan.FromSeconds(3);
            threadTimer.Start();
        }
        private void ButtonJoinSpecificRoom(object sender, RoutedEventArgs e)
        {
            threadTimer.Stop();
            string nameOfRoom = getRoomToJoin.Text;
            bool roomExistOrNot = false;
            uint roomId = 0;
            for (var i = 0; i < this.roomsResponse.rooms.Count; i++)
            {
                if (this.roomsResponse.rooms[i].name.Equals(nameOfRoom))
                {
                    roomExistOrNot = true;
                    roomId = this.roomsResponse.rooms[i].id;
                }
            }
            if (roomExistOrNot)
            {
                JoinRoomRequest request;
                request.roomId = roomId;
                string json = Helper.JoinRoomToJson(request);
                Connector.SendMessage(Helper.BuildMessage(messageConstants.joinRoom, json));
                string jsonAnswer = Connector.GetMessage();
                JoinRoomResponse responseJoinRoom = Helper.JsonToJoinRoom(jsonAnswer);
                if(responseJoinRoom.status == 0)
                {
                    threadTimer.Start();
                    issueWithRoomChoice.Text = "This Room Reached The Max Players.";
                    issueWithRoomChoice.Visibility = Visibility.Visible;
                }
                else
                {
                    issueWithRoomChoice.Visibility = Visibility.Hidden;
                    ShowPlayers showPlayersWindow = new ShowPlayers(mainWindow, roomId);
                    showPlayersWindow.WindowStartupLocation = WindowStartupLocation.CenterScreen;
                    showPlayersWindow.Show();
                    this.Visibility = Visibility.Hidden;
                }
            }
            else
            {
                threadTimer.Start();
                issueWithRoomChoice.Text = "This Room Does Not Exist.";
                issueWithRoomChoice.Visibility = Visibility.Visible;
            }
        }
        private void ButtonQuit(object sender, RoutedEventArgs e)
        {
            threadTimer.Stop();
            this.mainWindow.Visibility = Visibility.Visible;
            Close();
        }

        private void ButtonJoinRoom(object sender, EventArgs e)
        {
            Connector.SendMessage(Helper.BuildMessage(messageConstants.getRooms, ""));
            string jsonAnswer = Connector.GetMessage();
            GetRoomsResponseHelper response = Helper.JsonToGetRooms(jsonAnswer);
            if (response.rooms.Any())
            {
                this.roomsResponse.status = response.status;
                this.roomsResponse.rooms = new List<RoomData>();
                Rooms.Text = "";
                for (var i = 0; i < response.rooms.Count; i++)
                {
                    string infoAboutRoom = response.rooms[i];
                    Rooms.Text += infoAboutRoom.Split(",")[1] + "\n";
                    RoomData data = new RoomData();
                    data.id = uint.Parse(infoAboutRoom.Split(",")[0]);
                    data.name = infoAboutRoom.Split(",")[1];
                    data.maxPlayers = uint.Parse(infoAboutRoom.Split(",")[2]);
                    data.numOfQuestionsInGame = uint.Parse(infoAboutRoom.Split(",")[3]);
                    data.timePerQuestion = uint.Parse(infoAboutRoom.Split(",")[4]);
                    data.isActive = uint.Parse(infoAboutRoom.Split(",")[5]);
                    this.roomsResponse.rooms.Add(data);
                }
                getRoomToJoin.Visibility = Visibility.Visible;
                join.Visibility = Visibility.Visible;
            }
            else
            {
                Rooms.Text = "No Rooms Yet";
                getRoomToJoin.Visibility = Visibility.Hidden;
                join.Visibility = Visibility.Hidden;
            }
        }
    }
}