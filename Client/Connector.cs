using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Windows.Markup;

static class Constants
{
    public const int port = 8826;
    public const string ip = "127.0.0.1";
}

namespace Client
{
    class Connector
    {
        private static TcpClient socket;
        private static NetworkStream clientStream;
        public static void ConnectToServer()
        {
            try
            {
                socket = new TcpClient();
                IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(Constants.ip), Constants.port);
                socket.Connect(serverEndPoint);
                clientStream = socket.GetStream();
            }
            catch (Exception e)
            {
                throw new Exception();
            }
        }
        public static uint BytesToInt(byte [] buffer)
        {
            byte[] BytesOfSize = new byte[4];
            Array.Copy(buffer, buffer.Length - 4, BytesOfSize, 0, 4);
            Array.Reverse(BytesOfSize);
            uint size = BitConverter.ToUInt32(BytesOfSize, 0);
            return size;
        }
        public static string GetMessage()
        {
            byte[] buffer = new byte[4096];
            byte[] codeAndSize = new byte[5];
            int bytesRead = clientStream.Read(buffer, 0, 4096);
            Array.Copy(buffer, 0, codeAndSize, 0, 5);
            uint size = BytesToInt(codeAndSize);
            byte[] info = new byte[size];
            Array.Copy(buffer, 5, info, 0, size);
            string json = Encoding.UTF8.GetString(info, 0, (int)size);
            return json;
        }
        public static void SendMessage(byte[] buffer)
        {
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
        }
    }
}
