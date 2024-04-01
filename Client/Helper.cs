using Microsoft.VisualBasic;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Nodes;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows.Markup;

static class messageConstants
{
    public const int login = 5;
    public const int signUp = 7;
    public const int playersInRoom = 9;
    public const int joinRoom = 10;
    public const int createRoom = 11;
    public const int highScore = 12;
    public const int logout = 13;
    public const int getRooms = 14;
    public const int getStatistics = 15;
    public const int closeRoom = 16;
    public const int startGame = 17;
    public const int getRoomState = 18;
    public const int leaveRoom = 19;
    public const int leaveGame = 20;
    public const int getQuestion = 21;
    public const int submitAnswer = 22;
    public const int getGameResult = 23;
    public const int addQuestion = 24;
}

namespace Client
{
    class Helper
    {
        public static byte[] BuildMessage(int code, string json)
        {
            List<byte> message = new List<byte>();
            message.Add((byte)code);
            message.AddRange(BitConverter.GetBytes(json.Length).Reverse());
            message.AddRange(Encoding.UTF8.GetBytes(json));
            return message.ToArray();
        }
        public static string LoginToJson(LoginRequest request)
        {
            Dictionary<string, string> info = new Dictionary<string, string>();
            info.Add("username", request.username);
            info.Add("password", request.password);
            string json = JsonConvert.SerializeObject(info);
            return json;
        }
        public static string SignUpToJson(SignupRequest request)
        {
            Dictionary<string, string> info = new Dictionary<string, string>();
            info.Add("username", request.username);
            info.Add("password", request.password);
            info.Add("mail", request.email);
            string json = JsonConvert.SerializeObject(info);
            return json;
        }
        public static string GetPlayersInRoomToJson(GetPlayersInRoomRequest request)
        {
            Dictionary<string, string> info = new Dictionary<string, string>();
            info.Add("roomId", request.roomId.ToString());
            string json = JsonConvert.SerializeObject(info);
            return json;
        }
        public static string JoinRoomToJson(JoinRoomRequest request)
        {
            Dictionary<string, string> info = new Dictionary<string, string>();
            info.Add("roomId", request.roomId.ToString());
            string json = JsonConvert.SerializeObject(info);
            return json;
        }
        public static string CreateRoomToJson(CreateRoomRequest request)
        {
            Dictionary<string, string> info = new Dictionary<string, string>();
            info.Add("roomName", request.roomName);
            info.Add("maxUsers", request.maxUsers.ToString());
            info.Add("questionCount", request.questionCount.ToString());
            info.Add("answerTimeout", request.answerTimeout.ToString());
            string json = JsonConvert.SerializeObject(info);
            return json;
        }
        public static string SubmitAnswerToJson(SubmitAnswerRequest request)
        {
            Dictionary<string, string> info = new Dictionary<string, string>();
            info.Add("answerId", request.answerId.ToString());
            string json = JsonConvert.SerializeObject(info);
            return json;
        }
        public static string AddQuestionToJson(AddQuestionRequest request)
        {
            Dictionary<string, string> info = new Dictionary<string, string>();
            info.Add("question", request.question.ToString());
            info.Add("answer1", request.answer1.ToString());
            info.Add("answer2", request.answer2.ToString());
            info.Add("answer3", request.answer3.ToString());
            info.Add("answer4", request.answer4.ToString());
            info.Add("rightAnswer", request.rightAnswer.ToString());
            string json = JsonConvert.SerializeObject(info);
            return json;
        }
        public static LoginResponse JsonToLogin(string json)
        {
            LoginResponse response = JsonConvert.DeserializeObject<LoginResponse>(json);
            return response;
        }
        public static SignupResponse JsonToSignUp(string json)
        {
            SignupResponse response = JsonConvert.DeserializeObject<SignupResponse>(json);
            return response;
        }
        public static LogoutResponse JsonToLogout(string json)
        {
            LogoutResponse response = JsonConvert.DeserializeObject<LogoutResponse>(json);
            return response;
        }
        public static GetRoomsResponseHelper JsonToGetRooms(string json)
        {
            GetRoomsResponseHelper response = JsonConvert.DeserializeObject<GetRoomsResponseHelper>(json);
            return response;
        }
        public static GetPlayersInRoomResponse JsonToGetPlayersInRoom(string json)
        {
            string strings = "";
            string list = json.Substring(0, json.Length - 1);
            for (int i = 18; i < list.Length-1; i++)
            {
                strings += list[i];
            }
            GetPlayersInRoomResponse response = JsonConvert.DeserializeObject<GetPlayersInRoomResponse>(json);
            response.players = strings.Split(", ").ToList();
            return response;
        }
        public static GetHighScoreResponse JsonToGetHighScore(string json)
        {
            GetHighScoreResponse response = JsonConvert.DeserializeObject<GetHighScoreResponse>(json);
            return response;
        }
        public static GetPersonalStatsResponse JsonToGetPersonalStats(string json)
        {
            string strings = "";
            string list = json.Substring(0, json.Length-14);
            for (int i = 19; i < list.Length; i++)
            {
                strings += list[i];
            }
            for (int i = 0; i < strings.Length; i++)
            {
                strings = strings.Replace("\"", "");
                strings = strings.Replace("]", "");
            }
            List<string> result = strings.Split(',').ToList();
            GetPersonalStatsResponse response = JsonConvert.DeserializeObject<GetPersonalStatsResponse>(json);
            response.statistics = result;
            return response;
        }
        public static JoinRoomResponse JsonToJoinRoom(string json)
        {
            JoinRoomResponse response = JsonConvert.DeserializeObject<JoinRoomResponse>(json);
            return response;
        }
        public static CreateRoomResponse JsonToCreateRoom(string json)
        {
            CreateRoomResponse response = JsonConvert.DeserializeObject<CreateRoomResponse>(json);
            return response;
        }
        public static CloseRoomResponse JsonToCloseRoom(string json)
        {
            CloseRoomResponse response = JsonConvert.DeserializeObject<CloseRoomResponse>(json);
            return response;
        }
        public static StartGameResponse JsonToStartGame(string json)
        {
            StartGameResponse response = JsonConvert.DeserializeObject<StartGameResponse>(json);
            return response;
        }
        public static GetRoomStateResponse JsonToGetRoomState(string json)
        {
            GetRoomStateResponse response = JsonConvert.DeserializeObject<GetRoomStateResponse>(json);
            return response;
        }
        public static LeaveRoomResponse JsonToLeaveRoom(string json)
        {
            LeaveRoomResponse response = JsonConvert.DeserializeObject<LeaveRoomResponse>(json);
            return response;
        }
        public static LeaveGameResponse JsonToLeaveGame(string json)
        {
            LeaveGameResponse response = JsonConvert.DeserializeObject<LeaveGameResponse>(json);
            return response;
        }
        public static GetQuestionResponse JsonToGetQuestion(string json)
        {
            uint count = 0;
            GetQuestionResponseHelper response = JsonConvert.DeserializeObject<GetQuestionResponseHelper>(json);
            GetQuestionResponse finalResponse;
            finalResponse.status = response.status;
            finalResponse.question = response.question;
            List<string> result = response.answers.Split(',').ToList();
            Dictionary<uint, string> possibleAnswers = new Dictionary<uint, string>();
            foreach (string answer in result)
            {
                possibleAnswers[count] = answer;
                count++;
                if(count == 4)
                {
                    break;
                }
            }
            finalResponse.answers = possibleAnswers;
            return finalResponse;
        }
        public static SubmitAnswerResponse JsonToSubmitAnswer(string json)
        {
            SubmitAnswerResponse response = JsonConvert.DeserializeObject<SubmitAnswerResponse>(json);
            return response;
        }
        public static GetGameResultsResponse JsonToGetGameResults(string json)
        {
            GetGameResultsResponseHelper response = JsonConvert.DeserializeObject<GetGameResultsResponseHelper>(json);
            GetGameResultsResponse finalResponse;
            finalResponse.status = response.status;
            List<PlayerResults> results = new List<PlayerResults>();
            for (int i = 0; i < response.results.Count(); i++)
            {
                List<string> result = response.results[i].Split(',').ToList();
                PlayerResults playersResults;
                playersResults.username = result[0];
                playersResults.correctAnswerCount = uint.Parse(result[1]);
                playersResults.wrongAnswerCount = uint.Parse(result[2]);
                playersResults.averageAnswerTime = float.Parse(result[3]);
                results.Add(playersResults);
            }
            finalResponse.results = results;
            return finalResponse;
        }
        public static AddQuestionResponse JsonToAddQuestion(string json)
        {
            AddQuestionResponse response = JsonConvert.DeserializeObject<AddQuestionResponse>(json);
            return response;
        }
    }
}
