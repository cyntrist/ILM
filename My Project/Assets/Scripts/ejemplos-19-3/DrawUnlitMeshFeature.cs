using Unity.VisualScripting;
using UnityEditor;
using UnityEngine;
using UnityEngine.Rendering.Universal;

public class DrawUnlitMeshFeature : ScriptableRendererFeature
{
    [SerializeField] private Material material;
    [SerializeField] private Mesh mesh;
    [SerializeField] private string m_ShaderPass;
    [SerializeField]
    private RenderPassEvent _renderPassEvent;

    private DrawUnlitMeshPass m_pass;

    public override void Create()
    {
        m_pass = new DrawUnlitMeshPass();
        m_pass.renderPassEvent = RenderPassEvent.AfterRenderingPostProcessing;
    }

    // se llama una vez por frame
    public override void AddRenderPasses(ScriptableRenderer renderer, ref RenderingData renderingData)
    {
        if (renderingData.cameraData.cameraType != CameraType.Game)
            return;

        if (material == null || mesh == null)
            return;

        m_pass.Setup(material, mesh, m_ShaderPass);
        renderer.EnqueuePass(m_pass);
    }
}
