using Microsoft.AspNetCore.Mvc;
using Pruebas.Cliente.Models;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Web;

namespace Pruebas.Cliente.Controllers
{
    public class HomeController : Controller
    {
        #region "DLL WRAPPER FUNCTIONS "

        #region "TESSERACT"
        const string dll_Tesseract                    = "tesseract.dll";
        const string fn_GetTesseractOcrOutput         = "GetTesseractOcrOutput";
        const string fn_GetTesseractVersion           = "GetTesseractVersion";
     
        //////////////////////////////////////////////////////////////
        /// COMMON FUNCTION
        //////////////////////////////////////////////////////////////
   
        //////////////////////////////////////////////////////////////
        /// _GetTesseractOcrOutput
        //////////////////////////////////////////////////////////////
        [DllImport(@"" + dll_Tesseract + "", EntryPoint = @"" + fn_GetTesseractOcrOutput + "", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr _GetTesseractOcrOutput();

        [Microsoft.AspNetCore.Mvc.HttpGet(fn_GetTesseractOcrOutput)]
        public string GetTesseractOcrOutput()
        {
            //
            string return_value_str = string.Empty;
            //
            try
            {

                IntPtr intptr        = _GetTesseractOcrOutput();
                string unicodeString = Marshal.PtrToStringUTF8(intptr);

                return_value_str     = unicodeString;
            }
            catch (Exception ex)
            {
                string msg = ex.Message + " " + ex.StackTrace;

                return_value_str = msg;
            }
            return return_value_str;
        }

        
        //////////////////////////////////////////////////////////////
        /// GetTesseractVersion
        //////////////////////////////////////////////////////////////
        [DllImport(@"" + dll_Tesseract + "", EntryPoint = @"" + fn_GetTesseractVersion + "", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr _GetTesseractVersion();

        [Microsoft.AspNetCore.Mvc.HttpGet(fn_GetTesseractVersion)]
        public string GetTesseractVersion()
        {
            string return_value_str = string.Empty;
            IntPtr intptr           = IntPtr.Zero;

            try
            {
                // Call the external DLL function to get the result
                intptr               = _GetTesseractVersion();

                // Convert the IntPtr to a string
                string unicodeString = Marshal.PtrToStringUTF8(intptr);

                // Assign the result to the return value
                return_value_str     = unicodeString;


            }
            catch (Exception ex)
            {
                // Handle exceptions
                string msg = ex.Message + " " + ex.StackTrace;
                return_value_str = msg;
            }
            return return_value_str;
        }

        #endregion

        #region "TENSORFLOW"

        #endregion 

        #endregion

        #region "ROOT FUNCTIONS "

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

        #endregion 
    }
}