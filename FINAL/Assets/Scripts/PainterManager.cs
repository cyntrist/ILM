using Microsoft.Unity.VisualStudio.Editor;
using UnityEngine;

struct Paintbrush
{
    private string _name;

    Texture2D _brushTexture;
}


public class PainterManager : MonoBehaviour
{
    [SerializeField]
    private Color mainColor;

    private Color normalColor;

    private Paintbrush mainPaintbrush;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
