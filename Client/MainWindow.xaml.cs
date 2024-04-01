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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Media;

namespace Client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public const int SUCCESS = 100;
        private readonly SolidColorBrush PlaceholderBrush = Brushes.Gray;
        private readonly SolidColorBrush TextBrush = Brushes.Black;
        private readonly string PlaceholderTextUserName = "Shai&Adaya";
        private readonly string PlaceholderTextPass = "AreTheBest";
        public MainWindow()
        {
            InitializeComponent();
            try
            {
                Connector.ConnectToServer();
            }
            catch (Exception ex)
            {
                ServerError secondWindow = new ServerError();
                secondWindow.Show();
                this.Close();
            }
            this.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            SetPlaceholder();
            SoundPlayer music = new SoundPlayer();
            music.SoundLocation = AppDomain.CurrentDomain.BaseDirectory + "\\music.wav";
            //music.Play();
            CreateRoombt.IsEnabled = false;
            JoinRoombt.IsEnabled = false;
            Statisticsbt.IsEnabled = false;
            BestScoresbt.IsEnabled = false;
            AddQuestionsbt.IsEnabled = false;
        }
        private void SetPlaceholder()
        {
            usernameBox.Foreground = PlaceholderBrush;
            usernameBox.Text = PlaceholderTextUserName;
            passwordBox.Foreground = PlaceholderBrush;
            passwordBox.Text = PlaceholderTextPass;
        }
        public void ButtonLogout(object sender, RoutedEventArgs e)
        {
            Connector.SendMessage(Helper.BuildMessage(messageConstants.logout, ""));
            string jsonAnswer = Connector.GetMessage();
            issueWithLogin.Visibility = Visibility.Hidden;
            newClient.Visibility = Visibility.Hidden;
            Logoutbt.Visibility = Visibility.Hidden;
            LoggedOut();
        }
        public void LoggedOut()
        {
            Loginbt.IsEnabled = true;
            SignUpbt.IsEnabled = true;
            CreateRoombt.IsEnabled = false;
            JoinRoombt.IsEnabled = false;
            Statisticsbt.IsEnabled = false;
            BestScoresbt.IsEnabled = false;
            AddQuestionsbt.IsEnabled = false;
            Quit.IsEnabled = true;
            Quit.Visibility = Visibility.Visible;
            username.Visibility = Visibility.Visible;
            password.Visibility = Visibility.Visible;
            usernameBox.Visibility = Visibility.Visible;
            passwordBox.Visibility = Visibility.Visible;
            Loginbt.Visibility = Visibility.Visible;
            SignUpbt.Visibility = Visibility.Visible;
            issueWithLogin.Visibility = Visibility.Hidden;
            ClearSignInInfo();
            SetPlaceholder();
        }
        public void LoggedIn()
        {
            Loginbt.IsEnabled = false;
            SignUpbt.IsEnabled = false;
            CreateRoombt.IsEnabled = true;
            JoinRoombt.IsEnabled = true;
            Statisticsbt.IsEnabled = true;
            BestScoresbt.IsEnabled = true;
            AddQuestionsbt.IsEnabled = true;
            Quit.IsEnabled = false;
            Quit.Visibility = Visibility.Hidden;
            username.Visibility = Visibility.Hidden;
            password.Visibility = Visibility.Hidden;
            usernameBox.Visibility = Visibility.Hidden;
            passwordBox.Visibility = Visibility.Hidden;
            Loginbt.Visibility = Visibility.Hidden;
            issueWithLogin.Visibility = Visibility.Hidden;
        }
        private void ButtonSignUp(object sender, RoutedEventArgs e)
        {
            SignUp secondWindow = new SignUp(this);
            secondWindow.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            secondWindow.Show();
            this.Visibility = Visibility.Hidden;    
        }
        private void ButtonLogin(object sender, RoutedEventArgs e)
        {
            LoginRequest request;
            request.username = usernameBox.Text;
            request.password = passwordBox.Text;
            string json = Helper.LoginToJson(request);
            Connector.SendMessage(Helper.BuildMessage(messageConstants.login, json));
            string jsonAnswer = Connector.GetMessage();
            LoginResponse response = Helper.JsonToLogin(jsonAnswer);
            if(response.status == SUCCESS)
            {
                issueWithLogin.Visibility = Visibility.Hidden;
                LoggedIn();
                newClient.Text = "Hello " + usernameBox.Text;
                newClient.Visibility = Visibility.Visible;
                Logoutbt.Visibility = Visibility.Visible;
                Logoutbt.IsEnabled = true;
            }
            else
            {
                issueWithLogin.Visibility = Visibility.Visible;
                ClearSignInInfo();
                SetPlaceholder();
            }
        }

        private void ClearSignInInfo()
        {
            usernameBox.Text = string.Empty;
            passwordBox.Text = string.Empty;
        }
        private void ButtonCreateRoom(object sender, RoutedEventArgs e)
        {
            CreateRoom secondWindow = new CreateRoom(this);
            secondWindow.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            secondWindow.Show();
            this.Visibility = Visibility.Hidden;
        }
        private void ButtonJoinRoom(object sender, RoutedEventArgs e)
        {
            JoinRoom secondWindow = new JoinRoom(this);
            secondWindow.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            secondWindow.Show();
            this.Visibility = Visibility.Hidden;
        }
        private void ButtonStatus(object sender, RoutedEventArgs e)
        {
            Statistics secondWindow = new Statistics(this);
            secondWindow.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            secondWindow.Show();
            this.Visibility = Visibility.Hidden;
        }
        private void ButtonBestScores(object sender, RoutedEventArgs e)
        {
            BestScores secondWindow = new BestScores(this);
            secondWindow.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            secondWindow.Show();
            this.Visibility = Visibility.Hidden;
        }
        private void ButtonAddQuestion(object sender, RoutedEventArgs e)
        {
            AddQuestion secondWindow = new AddQuestion(this);
            secondWindow.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            secondWindow.Show();
            this.Visibility = Visibility.Hidden;
        }
        private void ButtonQuit(object sender, RoutedEventArgs e)
        {
            Close();
        }
        private void ButtonLoginInfo(object sender, RoutedEventArgs e)
        {
            MessageBox.Show(usernameBox.Text + " Logged In");
        }

        private void usernameBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (usernameBox.Text == PlaceholderTextUserName)
                usernameBox.Foreground = PlaceholderBrush;
            else
                usernameBox.Foreground = TextBrush;
        }
        private void passwordBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (passwordBox.Text == PlaceholderTextPass)
                passwordBox.Foreground = PlaceholderBrush;
            else
                passwordBox.Foreground = TextBrush;
        }
        private void txtInput_GotFocusUserName(object sender, RoutedEventArgs e)
        {
            if (usernameBox.Text == PlaceholderTextUserName)
            {
                usernameBox.Text = "";
                usernameBox.Foreground = TextBrush;
            }
        }
        private void txtInput_GotFocusPass(object sender, RoutedEventArgs e)
        {
            if (passwordBox.Text == PlaceholderTextPass)
            {
                passwordBox.Text = "";
                passwordBox.Foreground = TextBrush;
            }
        }
        private void txtInput_LostFocusUserName(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(usernameBox.Text))
                SetPlaceholder();
        }
        private void txtInput_LostFocusPass(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(passwordBox.Text))
                SetPlaceholder();
        }
    }
}
