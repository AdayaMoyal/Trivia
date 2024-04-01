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

namespace Client
{
    /// <summary>
    /// Interaction logic for BestScores.xaml
    /// </summary>
    public partial class BestScores : Window
    {
        private MainWindow mainWindow;
        public BestScores(MainWindow mainWindow)
        {
            InitializeComponent();
            this.mainWindow = mainWindow;
            ShowHighScores();
        }

        private void ButtonQuit(object sender, RoutedEventArgs e)
        {
            Close();
            mainWindow.Visibility = Visibility.Visible;
        }

        private GetHighScoreResponse SendAndGetMsgGetHighScore()
        {
            Connector.SendMessage(Helper.BuildMessage(messageConstants.highScore, ""));
            string jsonAnswer = Connector.GetMessage();
            return Helper.JsonToGetHighScore(jsonAnswer);
        }
        private void ShowHighScores()
        {
            GetHighScoreResponse highScoreResonse = SendAndGetMsgGetHighScore();
            List<string> highScoreList = highScoreResonse.statistics;
            if(highScoreList.Count() == 1)
            {
                first.Text = highScoreList[0];
                second.Text = "";
                third.Text = "";
            }
            else if(highScoreList.Count() == 2)
            {
                first.Text = highScoreList[0];
                second.Text = highScoreList[1];
                third.Text = "";
            }
            else if(highScoreList.Count() >= 3)
            {
                first.Text = highScoreList[0];
                second.Text = highScoreList[1];
                third.Text = highScoreList[2];
            }
            else if(highScoreList.Count() == 0)
            {
                first.Text = "No Players Yet";
                second.Text = "";
                third.Text = "";
            }
        }
    }
}
