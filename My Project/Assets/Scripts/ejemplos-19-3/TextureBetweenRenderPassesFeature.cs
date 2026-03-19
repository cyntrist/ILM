using Unity.VisualScripting;
using UnityEditor;
using UnityEngine;
using UnityEngine.Rendering.Universal;

public class TextureBetweenRenderPassesFeature : ScriptableRendererFeature
{
    [SerializeField] private Material material;
    [SerializeField] private Mesh mesh;
    [SerializeField] private string m_ShaderPass;
    [SerializeField]
    private RenderPassEvent _renderPassEvent;

    private DrawUnlitMeshPass m_pass;

    private AddOwnColorTexturePass m_pass1;
    private DrawUnlitMeshOnTexturePass m_pass2;

    public override void Create()
    {
        m_pass = new DrawUnlitMeshPass();
        m_pass.renderPassEvent = RenderPassEvent.AfterRenderingPostProcessing;
    }
}
