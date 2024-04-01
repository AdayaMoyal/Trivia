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
using System.Windows.Threading;

namespace Client
{
    /// <summary>
    /// Interaction logic for GameOver.xaml
    /// </summary>
    public partial class GameOver : Window
    {
        private MainWindow mainWindow;
        private DispatcherTimer threadTimer;
        public GameOver(MainWindow mainWindow)
        {
            InitializeComponent();
            this.mainWindow = mainWindow;
            Trophy.Visibility = Visibility.Hidden;
            threadTimer = new DispatcherTimer();
            threadTimer.Tick += GetGameResults;
            threadTimer.Interval = TimeSpan.FromSeconds(3);
            threadTimer.Start();
        }
        private void GetGameResults(object sender, EventArgs e)
        {
            results.Text = "";
            Trophy.Visibility = Visibility.Hidden;
            Connector.SendMessage(Helper.BuildMessage(messageConstants.getGameResult, ""));
            string jsonAnswer = Connector.GetMessage();
            GetGameResultsResponse responseGameResult = Helper.JsonToGetGameResults(jsonAnswer);
            if (responseGameResult.results.Count() == 0)
            {
                results.Text = "There's Players That Are Still Playing.\n Let's Wait For Them To Finish!";
            }
            else
            {
                threadTimer.Stop();
                Trophy.Visibility = Visibility.Visible;
                for (int i = 0; i < responseGameResult.results.Count(); i++)
                {
                    results.Text += responseGameResult.results[i].username + " - " + responseGameResult.results[i].correctAnswerCount + "\n";
                }
                
            }
        }
        private void ButtonQuit(object sender, RoutedEventArgs e)
        {
            mainWindow.Visibility = Visibility.Visible;
            Close();
        }
    }
}
