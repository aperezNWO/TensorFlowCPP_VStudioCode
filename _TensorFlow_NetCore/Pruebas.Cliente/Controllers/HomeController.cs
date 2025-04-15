using Microsoft.AspNetCore.Mvc;
using Pruebas.Cliente.Models;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Web;

namespace Pruebas.Cliente.Controllers
{
    public class HomeController : Controller
    {

      
        [DllImport(@"TensorFlowApp64_C.dll", EntryPoint = @"GetTensorFlowVersion", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr _GetTensorFlowVersion();

        [DllImport(@"TensorFlowApp64_CPP.dll", EntryPoint = @"GetTensorFlowOcrOutput", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr _GetTensorFlowOcrOutput();

        [DllImport(@"OCR_Tensorflow.dll", EntryPoint = @"performOCR", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr _performOCR();

        [Microsoft.AspNetCore.Mvc.HttpGet("GetTensorFlowVersion")]
        public string GetTensorFlowVersion()
        {
            //
            string return_value_str = string.Empty;
            //
            try
            {

                IntPtr intptr = _GetTensorFlowVersion();
                string unicodeString = Marshal.PtrToStringUTF8(intptr);

                return_value_str = unicodeString;
            }
            catch (Exception ex)
            {
                string msg = ex.Message + " " + ex.StackTrace;

                return_value_str = msg;
            }
            return return_value_str;
        }

        //
        [Microsoft.AspNetCore.Mvc.HttpGet("GetTensorFlowOcrOutput")]
        public string GetTensorFlowOcrOutput()
        {
            //
            string return_value_str = string.Empty;
            //
            try
            {

                IntPtr intptr        = _GetTensorFlowOcrOutput();
                string unicodeString = Marshal.PtrToStringUTF8(intptr);

                return_value_str = unicodeString;
            }
            catch (Exception ex)
            {
                string msg = ex.Message + " " + ex.StackTrace;

                return_value_str = msg;
            }
            return return_value_str;
        }

        //
        [Microsoft.AspNetCore.Mvc.HttpGet("performOCR")]
        public string performOCR()
        {
            //
            string return_value_str = string.Empty;
            //
            try
            {

                IntPtr intptr = _performOCR();
                string unicodeString = Marshal.PtrToStringUTF8(intptr);

                return_value_str = unicodeString;
            }
            catch (Exception ex)
            {
                string msg = ex.Message + " " + ex.StackTrace;

                return_value_str = msg;
            }
            return return_value_str;
        }

        private readonly ILogger<HomeController> _logger;

        public HomeController(ILogger<HomeController> logger)
        {
            _logger = logger;
        }

        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }

      

       
    }
}