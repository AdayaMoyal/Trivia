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
    /// Interaction logic for AddQuestion.xaml
    /// </summary>
    public partial class AddQuestion : Window
    {
        private MainWindow mainWindow;
        public AddQuestion(MainWindow mainWindow)
        {
            InitializeComponent();
            this.mainWindow = mainWindow;
            added.Visibility = Visibility.Hidden;
        }
        private void ButtonAddQuestion(object sender, RoutedEventArgs e)
        {
            AddQuestionRequest request;
            request.question = questionBox.Text;
            request.answer1 = answer1Box.Text;
            request.answer2 = answer2Box.Text;
            request.answer3 = answer3Box.Text;
            request.answer4 = answer4Box.Text;
            request.rightAnswer = rightAnswerBox.Text;
            string json = Helper.AddQuestionToJson(request);
            Connector.SendMessage(Helper.BuildMessage(messageConstants.addQuestion, json));
            string jsonAnswer = Connector.GetMessage();
            AddQuestionResponse response = Helper.JsonToAddQuestion(jsonAnswer);
            if(response.status == 515)
            {
                added.Visibility = Visibility.Visible;
            }
        }
        private void ButtonQuit(object sender, RoutedEventArgs e)
        {
            Close();
            mainWindow.Visibility = Visibility.Visible;
        }
    }
}
